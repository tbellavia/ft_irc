/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/20 15:13:24 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include "irc/Mode.hpp"
#include <iostream>

/**
 * @brief Construct a new IRC::CmdMODE object
 *
 * @param ctx the context of command builds (sender, channels etc...)
 * @param request the request of the command (needed to parse this)
 */

IRC::CmdMODE::CmdMODE(CmdCtx &ctx, std::string const &request):
	ACmd(ctx, request, "MODE"),
	m_target(""),
	m_authorized_modes(IRC_USER_MODE_STRING),
	m_parser(),
	m_mode_reply(),
	m_mode_arguments_reply()
{
	if (m_arguments.size() > 1)
		m_target = m_arguments[1];

	std::string parameter_modes;
	if (!m_target.empty() && Channel::is_valid_name(m_target))
	{
		m_authorized_modes = IRC_CHANNEL_MODE_STRING;
		parameter_modes = IRC_CHANNEL_PARAMETERS_MODE_STRING;
	}
	else
		parameter_modes = IRC_USER_PARAMETERS_MODE_STRING;

	if (m_arguments.size() > 2)
	{
		std::vector<std::string> mode_arguments;
		if (m_arguments.size() > 3)
			mode_arguments.assign(m_arguments.begin() + 3, m_arguments.end());

		m_parser = CmdMODEParse(
			m_arguments[2],
			mode_arguments,
			m_authorized_modes,
			parameter_modes
		);
	}
}

IRC::CmdMODE::CmdMODE(CmdMODE const &copy):
		ACmd(copy),
		m_target(copy.m_target),
		m_authorized_modes(copy.m_authorized_modes),
		m_parser(copy.m_parser),
		m_mode_reply(copy.m_mode_reply),
		m_mode_arguments_reply(copy.m_mode_arguments_reply)
{
}

IRC::CmdMODE::~CmdMODE()
{
}

IRC::Actions IRC::CmdMODE::execute() {
	std::cout << "Commmand MODE:";

	std::vector<std::string> m_arguments = this->parse();
	ReplyBuilder reply(this->server_name(), this->sender());

	if (m_target.empty())
	{
		return Actions::unique_send(
			this->sender(), reply.error_need_more_params(m_name)
		);
	}

	if (Channel::is_channel_name(m_target))
		return this->execute_channel_mode_(reply);

	std::cout << std::endl;
	return this->execute_user_mode_(reply);
}


/**
 * @brief Change channel options and mode in IRC
 *
 * @param args channel target and modes to change with their parameters
 * @param reply reply previously built
 * @return IRC::Actions actions to perform by the server
 */

IRC::Actions IRC::CmdMODE::execute_channel_mode_(
	ReplyBuilder &reply
) {
	User *sender = this->sender();
	std::string channel_name = m_target;
	Channel *channel = this->channels().find(channel_name);

	if (!channel)
		return Actions::unique_send(
			sender, reply.error_no_such_channel(channel_name)
		);

	if (channel->find(sender) == channel->end())
		return Actions::unique_send(
			sender, reply.error_not_on_channel(channel_name)
		);

	if (!channel->is_operator_user(sender))
		return Actions::unique_send(
			sender, reply.error_chan_o_privs_needed(channel_name)
		);

	if (m_arguments.size() == 2)
		return channel->notify(reply.reply_channel_mode_is(*channel));

	std::vector<std::pair<std::vector<Mode>, bool> > modes;
	try
	{
		modes = m_parser.parse();
	}
	catch (CmdMODEParse::ModeUnknownException const &e)
	{
		return Actions::unique_send(
			sender, reply.error_unknown_mode(e.mode())
		);
	}
	catch (CmdMODEParse::ArgumentMissingException const &)
	{
		return Actions::unique_idle();
	}

	std::vector<std::pair<std::vector<Mode>, bool> >::const_iterator first;
	first = modes.begin();
	std::vector<std::pair<std::vector<Mode>, bool> >::const_iterator last;
	last = modes.end();
	for (; first != last; ++first)
	{
		this->execute_channel_mode_list_(*channel, first->first, first->second);
	}

	return channel->notify(reply.reply_channel_mode_is(
		channel->get_name(), m_mode_reply, m_mode_arguments_reply
	));
}

void IRC::CmdMODE::execute_channel_mode_list_(
	Channel &channel,
	std::vector<Mode> const &mode_list,
	bool is_adding
)
{
	m_mode_reply += is_adding ? "+" : "-";
	for (std::size_t i = 0; i < mode_list.size(); ++i)
	{
		if (!mode_list[i].parameter.empty())
		{
			; // TODO: handle parameters modes
		}
		else if (is_adding && !(mode_list[i].value & channel.get_mode()))
		{
			m_mode_reply.push_back(mode_list[i].litteral);
			channel.set_mode(mode_list[i].value);
		}
		else if (!is_adding && mode_list[i].value & channel.get_mode())
		{
			m_mode_reply.push_back(mode_list[i].litteral);
			channel.unset_mode(mode_list[i].value);
		}
	}
}

/**
 * @brief Change users modes in IRC
 * Checks:
 *	if user targeted is the same that made the command,
 *	if user set its mode: if no just display its currently modes
 *	if modes are valids
 *
 * then change its modes if necessary and display its new modes
 *
 * @param reply the reply built previously
 * @return IRC::Actions actions sent to the server
 */

IRC::Actions IRC::CmdMODE::execute_user_mode_(ReplyBuilder &reply)
{
	User *sender = this->sender();

	std::cout << "Argument size " << m_arguments.size() << std::endl;

	if (sender->get_nickname() != m_target)
		return Actions::unique_send(
			sender, reply.error_users_dont_match()
		);

	if (m_arguments.size() == 2)
	{
		return Actions::unique_send(
			sender, reply.reply_u_mode_is(
				sender->get_nickname(), sender->get_mode()
			)
		);
	}

	std::vector<std::pair<std::vector<Mode>, bool> > modes;
	try
	{
 		modes = m_parser.parse();
	}
	catch (CmdMODEParse::ModeUnknownException const &)
	{
		return Actions::unique_send(
			sender, reply.error_u_mode_unknown_flag()
		);
	}
	catch (CmdMODEParse::ArgumentMissingException const &)
	{
		return Actions::unique_idle();
	}

	std::vector<std::pair<std::vector<Mode>, bool> >::const_iterator first;
	first = modes.begin();
	std::vector<std::pair<std::vector<Mode>, bool> >::const_iterator last;
	last = modes.end();

	for (; first != last; ++first)
	{
		this->execute_user_mode_list_(*sender, first->first, first->second);
	}

	return Actions::unique_send(
		sender, reply.reply_u_mode_is(
			sender->get_nickname(), m_mode_reply
		)
	);
}

void IRC::CmdMODE::execute_user_mode_list_(
	User &user,
	std::vector<Mode> const &mode_list,
	bool is_adding
)
{
	m_mode_reply += is_adding ? "+" : "-";
	for (std::size_t i = 0; i < mode_list.size(); ++i)
	{
		if (is_adding && !(mode_list[i].value & user.get_mode()))
		{
			m_mode_reply.push_back(mode_list[i].litteral);
			user.set_mode(mode_list[i].value);
		}
		else if (!is_adding && mode_list[i].value & user.get_mode())
		{
			m_mode_reply.push_back(mode_list[i].litteral);
			user.unset_mode(mode_list[i].value);
		}
	}
}
