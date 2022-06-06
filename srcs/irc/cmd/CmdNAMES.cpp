/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNAMES.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:07:09 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/06 23:08:29 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNAMES.hpp"

IRC::CmdNAMES::CmdNAMES(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "NAMES") {}

IRC::CmdNAMES::~CmdNAMES() { }

IRC::Actions
IRC::CmdNAMES::execute() {
	return Actions::unique_idle();
}