/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/16 16:03:56 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include "irc/Mode.hpp"
#include <iostream>

/**
 * @brief theses 4 static variables are helper to convert mode int to char mode
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

int IRC::CmdMODE::m_channel_modes[] = {
	IRC::CHAN_MODE_OPERATOR,
	IRC::CHAN_MODE_PRIVATE,
	IRC::CHAN_MODE_SECRET,
	IRC::CHAN_MODE_INVITE,
	IRC::CHAN_MODE_TOPIC_BY_OP,
	IRC::CHAN_MODE_NO_OUTSIDE,
	IRC::CHAN_MODE_MODERATED,
	IRC::CHAN_MODE_USER_LIMIT,
	IRC::CHAN_MODE_BAN_MASK,
	IRC::CHAN_MODE_VOICE,
	IRC::CHAN_MODE_KEY
};

char IRC::CmdMODE::m_channel_char_modes[] = "opsitnmlbvk";

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

	if ( args.size() == Expected_args(1) )
		return channel->notify(reply.reply_channel_mode_is(*channel));

	char is_valid;
	is_valid = this->is_mode_string_valid_(args[2], m_channel_char_modes);
	if ( is_valid >= 0 )
		return Actions::unique_send(sender, reply.error_unknown_mode(is_valid));

	std::vector<std::string> mode_list = this->parse_mode_string_(args[2]);
	std::vector<
		std::pair<std::string, std::vector<std::string> >
	> mode_list_with_args;
	mode_list_with_args = parse_mode_arguments_(
		mode_list, "olbvk", std::vector<std::string>(
			args.begin() + 3, args.end()
		)
	);

	Actions actions;
	for ( std::size_t i = 0; i < mode_list_with_args.size() ; ++i ) {
		if ( execute_channel_mode_list_(
			actions, reply, channel, mode_list_with_args[i]
		) )
			return Actions::unique_idle();
	}
	actions.push(channel->notify(reply.reply_channel_mode_is(*channel)));

	return actions;
}

int IRC::CmdMODE::execute_channel_mode_list_(
	Actions &actions,
	ReplyBuilder &reply,
	Channel *target,
	std::pair<std::string, std::vector<std::string> > const &mode_list
) {
	(void)actions;
	(void)reply;
	std::string const delimiters = "+-";
	std::string const channel_mode_args = "olbvk";

	bool is_add = true;
	std::size_t i = 0;
	std::string const &modes = mode_list.first;
	std::vector<std::string> const args = mode_list.second;
	if ( delimiters.find(modes[i]) != std::string::npos ) {
		if ( modes[i] == '-' )
			is_add = false;
		++i;
	}

	std::size_t arg_offset = 0;
	for ( ; i < modes.length(); ++i ) {
		std::size_t mode_arg = channel_mode_args.find(modes[i]);
		if ( mode_arg != std::string::npos ) {
			arg_offset++;
		}
		int *mode = char_to_channel_mode_(modes[i]);
		if ( is_add )
			target->set_mode(*mode);
		else
			target->unset_mode(*mode);
	}
	return 0;
}

/**
 * @brief Try to convert character mode to int mode
 *
 * @param c character mode
 * @return int* address of int mode, NULL if conversion is impossible
 */

int *IRC::CmdMODE::char_to_channel_mode_(char c) {
	for ( std::size_t i = 0; i < sizeof(m_channel_char_modes); ++i ) {
		if ( m_channel_char_modes[i] == c )
			return &m_channel_modes[i];
	}
	return NULL;
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

	if ( this->is_mode_string_valid_(args[2], m_char_modes) >= 0 )
		return Actions::unique_send(sender, reply.error_u_mode_unknown_flag());

	std::vector<std::string> mode_list = parse_mode_string_(args[2]);
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
 * @brief Check if string contains valid modes or not
 * 
 * @param mode_string the mode string
 * @param valid_modes the valid modes
 * @return char the invalid mode or -1 if all valids
 */

char IRC::CmdMODE::is_mode_string_valid_(
	std::string const &mode_string, std::string const &valid_modes
) {
	std::string const &delimiters = "+-";
	for ( std::size_t i = 0; i < mode_string.length(); ++i ) {
		if ( delimiters.find(mode_string[i]) != std::string::npos )
			++i;

		if ( valid_modes.find(mode_string[i]) == std::string::npos )
			return mode_string[i];
	}
	return -1;
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

/**
 * @brief Parse mode list with their arguments
 * 
 * @param mode_list vector of mode lists (+ob, -ob etc...)
 * @param mode_args the arguments to finds ("ob")
 * @param arguments the arguments passed by user as parameters (lperson, *.edu)
 * @return std::vector<
 * std::pair<std::string, std::vector<std::string> >
 * > a list of mode_list with their arguments attached as a list
 */

std::vector<
	std::pair<std::string, std::vector<std::string> >
> IRC::CmdMODE::parse_mode_arguments_(
	std::vector<std::string> const &mode_list,
	std::string const &mode_args,
	std::vector<std::string> const &arguments
) {
	std::vector<
		std::pair<std::string, std::vector<std::string> >
	> mode_list_with_args;
	std::size_t arg_len = 0;
	for ( std::size_t i = 0; i < mode_list.size(); ++i ) {

		std::vector<std::string> mode_arguments;
		for ( std::size_t j = 0; j < mode_list[i].length(); ++j ) {
			// If we find argument mode we append it to mode_arguments
			if ( mode_args.find(mode_list[i][j]) != std::string::npos ) {
				if ( arg_len < arguments.size() )
					mode_arguments.push_back(arguments[arg_len]);
				arg_len++;
			}

		}
		mode_list_with_args.push_back(
			std::make_pair(mode_list[i], mode_arguments)
		);
	}

	return mode_list_with_args;
}
