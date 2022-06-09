/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/09 11:46:36 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include "irc/Mode.hpp"
#include <iostream>
#include <sstream>

IRC::CmdMODE::setter_t const IRC::CmdMODE::m_parameters_func[
	IRC_CHANNEL_PARAMETERS_MODE_LEN
] = 
{
	&IRC::CmdMODE::set_channel_op_,
	&IRC::CmdMODE::set_channel_limit_,
	&IRC::CmdMODE::set_channel_ban_mask_,
	&IRC::CmdMODE::set_channel_voice_user_,
	&IRC::CmdMODE::set_channel_key_
};

/**
 * @brief Construct a new IRC::CmdMODE object
 *
 * Set up all parsing and context for execution
 * @param ctx the context of command builds (sender, channels etc...)
 * @param request the request of the command (needed to parse this)
 */

IRC::CmdMODE::CmdMODE(CmdCtx &ctx, std::string const &request):
	ACmd(ctx, request, "MODE"),
	m_target(""),
	m_mode_lists(),
	m_mode_arguments(),
	m_arg_cursor(0),
	m_mode_reply(),
	m_mode_arguments_reply()
{
	if (m_arguments.size() > 1)
		m_target = m_arguments[1];

	if (!m_target.empty() && Channel::is_valid_name(m_target))
	{
		m_authorized_modes = IRC_CHANNEL_MODE_STRING;
		m_parameter_modes = IRC_CHANNEL_PARAMETERS_MODE_STRING;
	}
	else
	{
		m_authorized_modes = IRC_USER_MODE_STRING;
		m_parameter_modes = IRC_USER_PARAMETERS_MODE_STRING;
	}

	if (m_arguments.size() > 2)
	{
		this->parse_modes_(m_arguments[2]);
		m_mode_arguments.assign(m_arguments.begin() + 3, m_arguments.end());
	}
}

IRC::CmdMODE::CmdMODE(CmdMODE const &copy):
		ACmd(copy),
		m_target(copy.m_target),
		m_authorized_modes(copy.m_authorized_modes),
		m_parameter_modes(copy.m_parameter_modes),
		m_mode_lists(copy.m_mode_lists),
		m_mode_arguments(copy.m_mode_arguments),
		m_arg_cursor(copy.m_arg_cursor),
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

	if (m_arguments.size() == 2)
		return Action::send(sender, reply.reply_channel_mode_is(*channel));

	Actions actions;
	for (std::size_t i = 0; i < m_mode_lists.size(); ++i)
	{
		this->execute_channel_mode_list_(
			actions, reply, *channel, m_mode_lists[i]
		);
	}

	if (!m_mode_reply.empty())
	{
		ReplyBuilder user_reply(this->sender()->get_mask());
		Actions reply_action = channel->notify(
			user_reply.reply_channel_mode(
				m_target, m_mode_reply, m_mode_arguments_reply
			)
		);
		actions.append(reply_action);
	}
	else if (actions.empty())
		return Actions::unique_idle();
	return actions;
}

void IRC::CmdMODE::execute_channel_mode_list_(
	Actions &actions,
	ReplyBuilder &reply,
	Channel &channel,
	std::string const &mode_list
)
{
	std::string const delimiters = "+-";
	bool is_add = true, writted = false;
	char correct_delimiter = '+';
	std::size_t i = 0;
	if (delimiters.find(mode_list[i]) != std::string::npos)
	{
		if (mode_list[i] == '-')
		{
			is_add = false;
			correct_delimiter = '-';
		}
		++i;
	}

	for (; i < mode_list.length(); ++i)
	{
		Mode mode = parse_one_mode_(mode_list[i]);
		if (mode.value < 0)
		{
			actions.push(Action(
				Event::SEND,
				this->sender(),
				reply.error_unknown_mode(mode_list[i])
			));
		}
		else if (
			this->execute_one_chan_mode_(is_add, mode, reply, actions, channel)
		)
		{
			if (!writted)
			{
				writted = true;
				m_mode_reply += correct_delimiter;
			}

			m_mode_reply += mode.litteral;
			if (mode.parameter)
				m_mode_arguments.push_back(*mode.parameter);
		}
	}
}

bool IRC::CmdMODE::execute_one_chan_mode_(
	bool to_add, Mode mode, ReplyBuilder &reply,
	Actions &actions, Channel &channel
)
{
	if (m_parameter_modes.find(mode.litteral) != std::string::npos)
	{
		if (mode.parameter && !channel.is_operator_user(this->sender()))
		{
			actions.push(IRC::Action(
				IRC::Event::SEND, this->sender(),
				reply.error_chan_o_privs_needed(channel.get_name())
			));
			return false;
		}

		for (std::size_t i = 0; i < m_parameter_modes.length(); ++i)
		{
			if (m_parameter_modes[i] == mode.litteral)
				return (this->*m_parameters_func[i])(
					to_add, reply, actions, channel, mode.parameter
				);
		}
	}
	else if (this->can_modified(to_add, mode, channel))
	{
		if (!channel.is_operator_user(this->sender()))
		{
			actions.push(IRC::Action(
				IRC::Event::SEND, this->sender(),
				reply.error_chan_o_privs_needed(channel.get_name())
			));
			return false;
		}
		if (!to_add)
			channel.unset_mode(mode.value);
		else
			channel.set_mode(mode.value);
		return true;
	}
	return false;
}

bool IRC::CmdMODE::can_modified(
	bool is_add, Mode const &mode, Channel const &channel
)
{
	return is_add != (channel.get_mode() & mode.value);
}

bool IRC::CmdMODE::set_channel_op_(
	bool to_add, ReplyBuilder &reply, Actions &actions,
	Channel &channel, std::string const *parameter
)
{
	if (!parameter)
	{
		/*
		actions.push(
			IRC::Action(
				Event::SEND, this->sender(),
				reply.error_need_more_params(m_name)
			)
		);
		*/
		return false;
	}

	Channel::const_iterator first = channel.begin();
	Channel::const_iterator last = channel.end();
	for (; first != last; ++first)
	{
		if ((*first)->get_nickname() == *parameter)
		{
			if (to_add && !channel.is_operator_user(*first))
			{
				channel.setOperator(*first);
				return true;
			}
			else if (!to_add && channel.is_operator_user(*first))
			{
				channel.unsetOperator(*first);
				return true;
			}
			return false;
		}
	}

	actions.push(
		IRC::Action(
			Event::SEND, this->sender(), reply.error_no_such_nick(*parameter)
		)
	);
	return false;
}

bool IRC::CmdMODE::set_channel_limit_(
	bool to_add, ReplyBuilder &reply, Actions &actions,
	Channel &channel, std::string const *parameter
)
{
	(void)reply;
	(void)actions;
	if (to_add && !parameter)
	{
		/*
		actions.push(
			IRC::Action(
				Event::SEND, this->sender(),
				reply.error_need_more_params(m_name)
			)
		);
		*/
		return false;
	}

	if (to_add)
	{
		std::stringstream ss(*parameter);
		std::size_t limit;
		ss >> limit;
		if (ss.fail() || static_cast<int>(limit) == channel.get_limit())
			return false;
	
		channel.set_limit(limit);
		return true;
	}
	else if (channel.get_limit() >= 0)
	{
		channel.set_limit(-1);
		return true;
	}
	return false;
}

bool IRC::CmdMODE::set_channel_ban_mask_(
	bool to_add, ReplyBuilder &reply, Actions &actions,
	Channel &channel, std::string const *parameter
)
{
	// List ban masks
	if (!parameter && to_add)
	{
		std::vector<std::string> const &ban_masks = channel.get_ban_masks();
		for (std::size_t i = 0; i < ban_masks.size(); ++i)
		{
			actions.push(
				Action::send(
					this->sender(),
					reply.reply_ban_list(channel.get_name() ,ban_masks[i])
				)
			);
		}
		actions.push(
			Action::send(
				this->sender(), reply.reply_end_of_ban_list(channel.get_name())
			)
		);
		return false;
	}

	if (!to_add && !parameter)
	{
		;// Error: need more params ?
	}

	// Add ban mask
	if (to_add && parameter)
	{
		std::vector<std::string> const &ban_masks = channel.get_ban_masks();
		std::vector<std::string>::const_iterator it = std::find(
			ban_masks.begin(), ban_masks.end(), *parameter
		);
		if (it == ban_masks.end())
		{
			channel.addBanMask(*parameter);
		}
		else
			return false;
		return true;
	}

	// Delete ban mask
	if (!to_add && parameter)
	{
		std::vector<std::string> const &ban_masks = channel.get_ban_masks();
		std::vector<std::string>::const_iterator it = std::find(
			ban_masks.begin(), ban_masks.end(), *parameter
		);
		if (it == ban_masks.end())
			return false;
		channel.deleteBanMask(*parameter);
		return true;
	}

	return false;
}

bool IRC::CmdMODE::set_channel_voice_user_(
	bool to_add, ReplyBuilder &reply, Actions &actions,
	Channel &channel, std::string const *parameter
)
{
	if (!parameter)
	{
		/*
		actions.push(
			IRC::Action(
				Event::SEND, this->sender(),
				reply.error_need_more_params(m_name)
			)
		);
		*/
		return false;
	}

	Channel::const_iterator first = channel.begin();
	Channel::const_iterator last = channel.end();
	for (; first != last; ++first)
	{
		if ((*first)->get_nickname() == *parameter)
		{
			if (to_add && !channel.is_voices_user(*first))
			{
				channel.allowVoice(*first);
				return true;
			}
			else if (!to_add && channel.is_voices_user(*first))
			{
				channel.disallowVoice(*first);
				return true;
			}
			return false;
		}
	}

	actions.push(
		IRC::Action(
			Event::SEND, this->sender(), reply.error_no_such_nick(*parameter)
		)
	);
	return false;
}

bool IRC::CmdMODE::set_channel_key_(
	bool to_add, ReplyBuilder &reply, Actions &actions,
	Channel &channel, std::string const *parameter
)
{
	if (to_add && parameter)
	{
		std::string const *key = channel.get_key();
		if (key)
		{
			actions.push(
				IRC::Action(
					Event::SEND, this->sender(), reply.error_key_set(
						channel.get_name()
					)
				)
			);
		}
		else
		{
			channel.set_key(*parameter);
			return true;
		}
	}
	else if (!to_add && parameter)
	{
		std::string const *key = channel.get_key();
		if (key && *key == *parameter)
		{
			channel.unset_key(*parameter);
			return true;
		}
	}
	return false;
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

	Actions actions;
	for (std::size_t i = 0; i < m_mode_lists.size(); ++i)
	{
		this->execute_user_mode_list_(actions, reply, *sender, m_mode_lists[i]);
	}

	if (!m_mode_reply.empty())
	{
		ReplyBuilder user_reply(sender->get_mask());
		Actions reply_action = Actions::unique_send(
			sender, user_reply.reply_user_mode(m_target, m_mode_reply)
		);
		actions.append(reply_action);
	}
	return actions;
}

void IRC::CmdMODE::execute_user_mode_list_(
	Actions &actions,
	ReplyBuilder &reply,
	User &user,
	std::string const &mode_list
)
{
	std::string const delimiters = "+-";
	bool is_add = true, already_written = false;
	std::size_t i = 0;
	if (delimiters.find(mode_list[i]) != std::string::npos)
	{
		if (mode_list[i] == '-')
			is_add = false;
		++i;
	}

	for (; i < mode_list.length(); ++i)
	{
		Mode mode = parse_one_mode_(mode_list[i]);
		if (mode.value < 0)
		{
			actions.push(Action(
				Event::SEND, this->sender(), reply.error_u_mode_unknown_flag()
			));
		}
		else if (m_parameter_modes.find(mode.litteral) != std::string::npos)
		{
			; // TODO: handle parameters
		}
		else if (is_add && !(user.get_mode() & mode.value))
		{
			if (!already_written)
			{
				already_written = true;
				m_mode_reply += "+";
			}
			user.set_mode(mode.value);
			m_mode_reply += mode.litteral;
		}
		else if (!is_add && user.get_mode() & mode.value)
		{
			if (!already_written)
			{
				already_written = true;
				m_mode_reply += "-";
			}
			user.unset_mode(mode.value);
			m_mode_reply += mode.litteral;
		}
	}
}

/**
 * @brief Construct one mode from c
 * 
 * @param c litteral character
 * @return IRC::Mode the newly constructed mode
 */

IRC::Mode IRC::CmdMODE::parse_one_mode_(char c)
{
	int value = char_to_mode_(c);
	std::string const *parameter = NULL;

	if (
		m_parameter_modes.find(c) != std::string::npos 
		&& m_arg_cursor < m_mode_arguments.size()
	)
	{
		parameter = new std::string(m_mode_arguments[m_arg_cursor]);
		m_arg_cursor++;
	}

	return Mode(value, c, parameter);
}

/**
 * @brief Parse mode string into vector of mode lists
 *
 * @return std::vector<std::string> 
 */

void IRC::CmdMODE::parse_modes_(std::string const &mode_string)
{
	std::string const delimiters = "+-";
	for (std::size_t i = 0, new_pos; i < mode_string.length(); i = new_pos)
	{
		new_pos = i;
		// Advance 1 if delimiter
		if (delimiters.find(mode_string[new_pos]) != std::string::npos)
			++new_pos;

		// Find until next delimiter or end
		while (
			new_pos < mode_string.length()
			&& delimiters.find(mode_string[new_pos]) == std::string::npos
		)
			++new_pos;

		m_mode_lists.push_back(
			mode_string.substr(i, new_pos - i)
		);
	}
}

/**
 * @brief Take litteral c to return value of mode
 * 
 * @param c the litteral converted
 * @return int the value of the mode found or -1 if not found
 */

int IRC::CmdMODE::char_to_mode_(char c)
{
	std::size_t pos = m_authorized_modes.find(c);
	if (pos == std::string::npos)
		return -1;
	return 0x01 << pos;
}
