/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdLIST.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:12:50 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/13 14:46:06 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdLIST.hpp"

IRC::CmdLIST::CmdLIST(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "LIST")
{
}

IRC::CmdLIST::CmdLIST(CmdLIST const &copy):
		ACmd(copy)
{
}

IRC::CmdLIST::~CmdLIST()
{
}

IRC::Actions IRC::CmdLIST::execute()
{
	return IRC::Actions::unique_idle();
}

IRC::CmdLIST &IRC::CmdLIST::operator=(CmdLIST const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
