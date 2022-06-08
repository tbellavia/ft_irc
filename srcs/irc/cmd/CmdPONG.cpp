/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPONG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:22:51 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/08 13:51:21 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CmdPONG.hpp"
# include <iostream>

IRC::CmdPONG::CmdPONG(CmdCtx &ctx, std::string const &request) : 
	ACmd(ctx, request, "PONG") { }

IRC::CmdPONG::~CmdPONG() { }

IRC::Actions
IRC::CmdPONG::execute() {
	ReplyBuilder reply(this->server_name(), this->sender());

	if (m_arguments.size() != Expected_args(1)) {
		return Actions::unique_send(this->sender(), reply.error_no_origin());
	}

	// Just ignore pong messsages
	return Actions::unique_idle();
}
