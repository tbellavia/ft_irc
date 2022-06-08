/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPING.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:41:25 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/08 14:16:44 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdPING.hpp"

IRC::CmdPING::CmdPING(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "PING")
{
}

IRC::CmdPING::CmdPING(CmdPING const &copy):
		ACmd(copy)
{
}

IRC::CmdPING::~CmdPING()
{
}

IRC::Actions IRC::CmdPING::execute()
{
	ReplyBuilder reply(this->server_name(), this->sender());
	if (m_arguments.size() != Expected_args(1)) {
		return Actions::unique_send(this->sender(), reply.error_no_origin());
	}

	// Response the pong
	return Actions::unique_send(
		this->sender(), reply.reply_pong(m_arguments[1])
	);
}

IRC::CmdPING &IRC::CmdPING::operator=(IRC::CmdPING const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
