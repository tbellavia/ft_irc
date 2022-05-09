/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/09 14:05:48 by lperson-         ###   ########.fr       */
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

	if ( args.size() != Expected_args(1) )
		return IRC::Actions::unique_send(
			this->sender(), reply.error_need_more_params("MODE")
		);

	if ( !this->sender()->connected() )
		return IRC::Actions::unique_idle();

	std::cout << std::endl;
	return IRC::Actions::unique_idle();
}
