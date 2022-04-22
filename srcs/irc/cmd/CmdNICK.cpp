/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:18:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 01:32:20 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNICK.hpp"
#include <iostream>

IRC::CmdNICK::CmdNICK(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request) { }

IRC::CmdNICK::~CmdNICK() { }

/**
 * NICK
 * 
 * NICK <nickname>
 */
void
IRC::CmdNICK::execute() {
	User &user = m_ctx.sender;
	std::vector<std::string> args = ft::split(m_request);
	
	std::cout << "CmdNICK" << std::endl;
	if ( args.size() != 2 ){
		user.update("Wrong number of argument");
	} else {
		std::string nick = args[1];

		if ( !user.mode_isset(MODE_ONBOARD) ){
			user.set_nick(nick);
		}
	}
}