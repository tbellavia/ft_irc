/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/19 12:05:54 by lperson-         ###   ########.fr       */
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
	m_parser()
{
	if (m_arguments.size() > 1)
		m_target = m_arguments[1];

	if (!m_target.empty() && Channel::is_valid_name(m_target))
		m_authorized_modes = IRC_CHANNEL_MODE_STRING;

	if (m_arguments.size() > 3)
	{
		std::vector<std::string> mode_arguments(
			m_arguments.begin() + 2,
			m_arguments.end()
		);
		m_parser = CmdMODEParse(
			m_arguments[2],
			mode_arguments,
			m_authorized_modes
		);
	}
}

IRC::CmdMODE::CmdMODE(CmdMODE const &copy):
		ACmd(copy),
		m_parser(copy.m_parser)
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
		return Actions::unique_send(
			this->sender(), reply.error_need_more_params(m_name)
		);

	if (Channel::is_channel_name(m_target))
		return this->execute_channel_mode_(m_arguments, reply);

	std::cout << std::endl;
	return this->execute_user_mode_(m_arguments, reply);
}

IRC::Actions IRC::CmdMODE::execute_channel_mode_(
	std::vector<std::string> const &m_arguments, ReplyBuilder &reply
) {
	User *sender = this->sender();
	std::string channel_name = m_arguments[1];
	Channel *channel = this->channels().find(channel_name);

	if ( !channel )
		return Actions::unique_send(
			sender, reply.error_no_such_channel(channel_name)
		);

	if ( channel->find(sender) == channel->end() )
		return Actions::unique_send(
			sender, reply.error_not_on_channel(channel_name)
		);

	if ( !channel->is_operator_user(sender) )
		return Actions::unique_send(
			sender, reply.error_chan_o_privs_needed(channel_name)
		);

	return Actions::unique_idle();
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
 * @param m_arguments user target and modes to change
 * @param reply the reply built previously
 * @return IRC::Actions actions sent to the server
 */

IRC::Actions IRC::CmdMODE::execute_user_mode_(
	std::vector<std::string> const &m_arguments, ReplyBuilder &reply
) {
	User *sender = this->sender();

	if ( sender->get_nickname() != m_target )
		return Actions::unique_send(
			sender, reply.error_users_dont_match()
		);

	if ( m_arguments.size() == Expected_args(1) ) {
		return Actions::unique_send(
			sender, reply.reply_u_mode_is(
				sender->get_nickname(), sender->get_mode()
			)
		);
	}

	std::vector<std::string> const &mode_list = m_parser.mode_list();
	if (!this->is_mode_users_valid_(mode_list))
		return Actions::unique_send(sender, reply.error_u_mode_unknown_flag());

	for ( std::size_t i = 0; i < mode_list.size(); ++i ) {
		if ( mode_list[i][0] == '-' )
			delete_mode_list_to_user_(sender, mode_list[i]);
		else
			add_mode_list_to_user_(sender, mode_list[i]);
	}

	return Actions::unique_send(
		sender, reply.reply_u_mode_is(
			sender->get_nickname(), sender->get_mode()
		)
	);
}

/**
 * @brief Set modes for user
 * 
 * @param target user modified
 * @param mode_list list of modes set in user
 */

void IRC::CmdMODE::add_mode_list_to_user_(
	User *target, std::string const &mode_list
) {
	std::size_t i = mode_list[0] == '+' ? 1 : 0;
	for ( ; i < mode_list.length(); ++i ) {
		int mode = this->char_to_mode_(mode_list[i]);
		target->set_mode(mode);
	}
}

/**
 * @brief Unset modes for user
 * 
 * @param target user modified
 * @param mode_list list of modes unset in user
 */

void IRC::CmdMODE::delete_mode_list_to_user_(
	User *target, std::string const &mode_list
) {
	for ( std::size_t i = 1; i < mode_list.length(); ++i ) {
		int mode = this->char_to_mode_(mode_list[i]);
		target->unset_mode(mode);
	}
}

/**
 * @brief Check if list of mode operations contains valid nodes
 * 
 * @param mode_lists the list of mode operations
 * @return true if valid
 * @return false if not valid (contains unknown mode)
 */

bool IRC::CmdMODE::is_mode_users_valid_(
	std::vector<std::string> const &mode_lists
) {
	std::string delimiters = "+-";
	for ( std::size_t i = 0; i < mode_lists.size(); ++i ) {
		if ( mode_lists[i].length() == 1 )
			return false;

		std::size_t d = delimiters.find(mode_lists[i][0]) != std::string::npos ?
			1 :
			0;
		for ( ; d < mode_lists[i].length(); ++d )
			if ( !this->char_to_mode_(mode_lists[i][d]) )
				return false;
	}
	return true;
}

/**
 * @brief Character c to mode
 * 
 * @param c the character to converts
 * @return the actual mode value or -1 if inexistant
 */

int IRC::CmdMODE::char_to_mode_(char c)
{
	for (std::string::size_type i = 0; i < m_authorized_modes.length(); ++i)
	{
		if (m_authorized_modes[i] == c)
			return (1UL << i);
	}

	return -1;
}
