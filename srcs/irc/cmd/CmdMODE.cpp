/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:52:41 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/09 13:09:09 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE.hpp"

IRC::CmdMODE::CmdMODE(CmdCtx &ctx, std::string &request):
	ACmd(ctx, request, "MODE") { }

IRC::CmdMODE::~CmdMODE() { }

IRC::Actions IRC::CmdMODE::execute() {
	return IRC::Actions::unique_idle();
}
