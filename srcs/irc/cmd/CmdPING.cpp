/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPING.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:22:51 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 21:59:18 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CmdPING.hpp"
# include <iostream>

IRC::CmdPING::CmdPING(CmdCtx &ctx, std::string const &request) : ACmd(ctx, request) { }

IRC::CmdPING::~CmdPING() { }

void
IRC::CmdPING::execute() {
	std::cout << "CmdPING: " << m_request << std::endl;
	m_ctx.sender.update("PONG");
}