/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKILL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:22:18 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/15 09:26:20 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc/cmd/CmdKILL.hpp"

IRC::CmdKILL::CmdKILL(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "KILL")
{
}

IRC::CmdKILL::CmdKILL(CmdKILL const &copy):
		ACmd(copy)
{
}

IRC::CmdKILL::~CmdKILL()
{
}

IRC::Actions IRC::CmdKILL::execute()
{
	return Actions::unique_idle();
}

IRC::CmdKILL &IRC::CmdKILL::operator=(CmdKILL const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
