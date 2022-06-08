/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPONG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:22:51 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/08 13:15:25 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CmdPONG.hpp"
# include <iostream>

IRC::CmdPONG::CmdPONG(CmdCtx &ctx, std::string const &request) : 
	ACmd(ctx, request, "PONG") { }

IRC::CmdPONG::~CmdPONG() { }

IRC::Actions
IRC::CmdPONG::execute() {
	return Actions::unique_send(m_ctx.sender, "PING");
}