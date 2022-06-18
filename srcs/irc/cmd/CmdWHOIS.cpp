/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHOIS.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:58:02 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/18 21:17:55 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdWHOIS.hpp"

IRC::CmdWHOIS::CmdWHOIS(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "WHOIS") { }

IRC::CmdWHOIS::~CmdWHOIS() { }

IRC::Actions
IRC::CmdWHOIS::execute() {
	return Actions::unique_idle();
}