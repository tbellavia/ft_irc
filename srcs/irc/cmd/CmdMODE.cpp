/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/12 12:01:50 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include "irc/Mode.hpp"
#include <iostream>

/**
 * @brief theses 2 static variables are helper to convert mode int to char mode
 */

int IRC::CmdMODE::m_modes[] = {
	IRC::MODE_AWAY,
	IRC::MODE_INVISIBLE,
	IRC::MODE_WALLOPS,
	IRC::MODE_RESTRICTED,
	IRC::MODE_OPERATOR,
	IRC::MODE_LOCAL_OPERATOR
};

char IRC::CmdMODE::m_char_modes[] = "aiwroO";

IRC::CmdMODE::CmdMODE(CmdCtx &ctx, std::string const &request):
	ACmd(ctx, request, "MODE") { }

IRC::CmdMODE::~CmdMODE() { }

IRC::Actions IRC::CmdMODE::execute() {
	std::cout << "Commmand MODE:";

	std::vector<std::string> args = this->parse();
	ReplyBuilder reply(this->server_name(), this->sender());

	if ( args.size() < Expected_args(1) )
		return Actions::unique_send(
			this->sender(), reply.error_need_more_params("MODE")
		);
	if ( Channel::is_channel_name(args[1]) )
		return this->execute_channel_mode_(args, reply);

	std::cout << std::endl;
	return this->execute_user_mode_(args, reply);
}


/**
 * @brief Change channel options and mode in IRC
 *
 * @param args channel target and modes to change with their parameters
 * @param reply reply previously built
 * @return IRC::Actions actions to perform by the server
 */

IRC::Actions IRC::CmdMODE::execute_channel_mode_(
	std::vector<std::string> const &args, ReplyBuilder &reply
) {
	User *sender = this->sender();
	std::string channel_name = args[1];
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

	return channel->notify(reply.reply_channel_mode_is(*channel));
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
 * @param args user target and modes to change
 * @param reply the reply built previously
 * @return IRC::Actions actions sent to the server
 */

IRC::Actions IRC::CmdMODE::execute_user_mode_(
	std::vector<std::string> const &args, ReplyBuilder &reply
) {
	User *sender = this->sender();
	std::string const target_name = args[1];

	if ( sender->get_nickname() != target_name )
		return Actions::unique_send(
			sender, reply.error_users_dont_match()
		);

	if ( args.size() == Expected_args(1) ) {
		return Actions::unique_send(
			sender, reply.reply_u_mode_is(
				sender->get_nickname(), sender->get_mode()
			)
		);
	}

	std::vector<std::string> mode_list = parse_mode_string_(args[2]);
	if ( !this->is_mode_users_valid_(mode_list) )
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
		int *mode = this->char_to_mode_(mode_list[i]);
		target->set_mode(*mode);
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
		int *mode = this->char_to_mode_(mode_list[i]);
		target->unset_mode(*mode);
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
 * @return int* pointer to the mode value or NULL if inexistant
 */

int *IRC::CmdMODE::char_to_mode_(char c) {
	for ( std::size_t i = 0; i < sizeof(m_char_modes); ++i )
		if ( m_char_modes[i] == c )
			return m_modes + i;
	return NULL;
}

/**
 * @brief Parse simple mode string into array of modes strings
 * Each strings in array will begin with '+' or '-' and a list of mods to modify
 *
 * @param mode_string the string with mode operations
 * @return std::vector<std::string> the differents list of modes operations
 */

std::vector<std::string> IRC::CmdMODE::parse_mode_string_(
	std::string const &mode_string
) const {
	std::string const delimiters("+-");
	std::vector<std::string> mode_list;

	for (
		std::size_t i = 0, next_pos; i < mode_string.length(); i = next_pos
	) {
		next_pos = i;
		// Advance next_pos when delimiter
		if ( delimiters.find( mode_string[next_pos] ) != std::string::npos )
			++next_pos;

		// Advance next_pos until delimiter or end of string
		for ( ; next_pos < mode_string.length() ; ++next_pos) {
			if ( delimiters.find(mode_string[next_pos]) != std::string::npos ) {
				break;
			}
		}

		std::size_t length = next_pos - i;
		// Push one list of commands to appends or delete
		mode_list.push_back(
			mode_string.substr(i, length)
		);
	}
	return mode_list;
}
