/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTOPIC.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:00:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/05 23:06:55 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdTOPIC.hpp"

IRC::CmdTOPIC::CmdTOPIC(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "TOPIC") { }

IRC::CmdTOPIC::~CmdTOPIC() { }

IRC::Actions
IRC::CmdTOPIC::execute() {
	return Actions::unique_idle();
}