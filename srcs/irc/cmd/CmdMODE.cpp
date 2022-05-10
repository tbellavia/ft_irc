/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/10 15:37:45 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include <iostream>

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

	return Actions::unique_idle();
}

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
	for ( std::size_t i = 0; i < mode_list.size(); ++i ) {
		std::cout << mode_list[i] << std::endl;
	}

	return Actions::unique_idle();
}

/**
 * @brief Parse simple mode string into array of modes strings
 * Each strings in array will begin with '+' or '-' and a list of mods to modify
 *
 * @param mode_string 
 * @return std::vector<std::string> 
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
