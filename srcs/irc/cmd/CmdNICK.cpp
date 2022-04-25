/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:18:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/26 01:36:33 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNICK.hpp"
#include <iostream>

IRC::CmdNICK::CmdNICK(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "NICK") { }

IRC::CmdNICK::~CmdNICK() { }

/**
 * NICK
 * 
 * NICK <nickname>
 */
IRC::Actions
IRC::CmdNICK::execute() {
	User *user = m_ctx.sender;
	std::vector<std::string> args = ft::split(m_request);
	
	std::cout << "CmdNICK" << std::endl;
	if ( args.size() != 2 ){
		return Actions::unique_send(user, "wrong number of arguments");
	} else {
		std::string nick = args[1];

		if ( !user->mode_isset(MODE_ONBOARD) ){
			user->set_nick(nick);
		}
	}
	return Actions::unique_idle();
}