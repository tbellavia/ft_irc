/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdINVITE.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:20:12 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/08 16:26:39 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdINVITE.hpp"

IRC::CmdINVITE::CmdINVITE(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "INVITE")
{
}

IRC::CmdINVITE::CmdINVITE(CmdINVITE const &copy):
		ACmd(copy)
{
}

IRC::CmdINVITE::~CmdINVITE()
{
}

IRC::Actions IRC::CmdINVITE::execute()
{
	return Actions::unique_idle();
}

IRC::CmdINVITE &IRC::CmdINVITE::operator=(CmdINVITE const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
