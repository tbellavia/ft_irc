/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPONG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:22:51 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 15:27:04 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CmdPONG.hpp"
# include <iostream>

IRC::CmdPONG::CmdPONG(CmdCtx &ctx, std::string const &request) : ACmd(ctx, request) { }

IRC::CmdPONG::~CmdPONG() { }

void
IRC::CmdPONG::execute() {
	std::cout << "CmdPING: " << m_request << std::endl;
	m_ctx.sender.update("PING");
}