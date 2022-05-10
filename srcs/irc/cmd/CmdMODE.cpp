/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/10 11:58:26 by lperson-         ###   ########.fr       */
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

	return Actions::unique_idle();
}
