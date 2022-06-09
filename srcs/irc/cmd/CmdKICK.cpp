/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:42 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/09 13:57:45 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc/cmd/CmdKICK.hpp"

IRC::CmdKICK::CmdKICK(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "KICK")
{
}

IRC::CmdKICK::CmdKICK(CmdKICK const &copy):
		ACmd(copy)
{
}

IRC::CmdKICK::~CmdKICK()
{
}

IRC::Actions IRC::CmdKICK::execute()
{
	return Actions::unique_idle();
}

IRC::CmdKICK &IRC::CmdKICK::operator=(IRC::CmdKICK const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
