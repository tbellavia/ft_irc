/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/09 14:26:40 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"
#include <iostream>

IRC::CmdMODE::CmdMODE(CmdCtx &ctx, std::string const &request):
	ACmd(ctx, request, "MODE") {
		std::cout << "HELLO" << std::endl;
	}

IRC::CmdMODE::~CmdMODE() { }

IRC::Actions IRC::CmdMODE::execute() {
	std::cout << "Commmand MODE:";

	std::vector<std::string> args = this->parse();
	ReplyBuilder reply(this->server_name(), this->sender());

	if ( args.size() < Expected_args(1) )
		return IRC::Actions::unique_send(
			this->sender(), reply.error_need_more_params("MODE")
		);
	if ( IRC::Channel::is_channel_name(args[1]) )
		return this->execute_channel_mode_(args, reply);

	std::cout << std::endl;
	return IRC::Actions::unique_idle();
}

IRC::Actions IRC::CmdMODE::execute_channel_mode_(
	std::vector<std::string> const &args, ReplyBuilder &reply
) {
	Channel *channel = this->channels().find(args[1]);
	if (!channel)
		return IRC::Actions::unique_send(
			this->sender(), reply.error_no_such_channel(args[1])
		);

	return Actions::unique_idle();
}
