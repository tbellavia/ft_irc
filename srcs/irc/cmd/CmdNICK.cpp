/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:18:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 17:16:11 by bbellavi         ###   ########.fr       */
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
IRC::Action
IRC::CmdNICK::execute() {
	User *user = m_ctx.sender;
	std::vector<std::string> args = ft::split(m_request);
	
	std::cout << "CmdNICK" << std::endl;
	if ( args.size() != 2 ){
		return Action::send(user, "wrong number of arguments");
	} else {
		std::string nick = args[1];

		if ( !user->mode_isset(MODE_ONBOARD) ){
			user->set_nick(nick);
		}
	}
	return Action::idle();
}