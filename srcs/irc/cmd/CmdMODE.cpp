/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/09 13:48:58 by lperson-         ###   ########.fr       */
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
	std::cout << std::endl;
	return IRC::Actions::unique_idle();
}
