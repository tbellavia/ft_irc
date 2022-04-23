/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPONG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:22:51 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 17:42:06 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CmdPONG.hpp"
# include <iostream>

IRC::CmdPONG::CmdPONG(CmdCtx &ctx, std::string const &request) : ACmd(ctx, request) { }

IRC::CmdPONG::~CmdPONG() { }

IRC::Action
IRC::CmdPONG::execute() {
	return Action::send(m_ctx.sender, "PING");
}