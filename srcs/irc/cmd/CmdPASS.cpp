/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPASS.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:00:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 01:38:37 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdPASS.hpp"
#include <iostream>

IRC::CmdPASS::CmdPASS(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request) { }

IRC::CmdPASS::~CmdPASS() { }

/**
 * Pass
 * 
 * Pass password
 * The pass command takes a password and change the user state from
 * MODE_ONBOARD to MODE_REGULAR.
 * If a user is in a MODE_ONBOARD state, it cannot do anything on
 * the server.
 */
void
IRC::CmdPASS::execute() {
	User &user = m_ctx.sender;
	std::vector<std::string> args = ft::split(m_request);
	
	std::cout << "CmdPASS: " << m_request << std::endl;
	if ( args.size() != 2 ){
		user.update("Wrong number of arguments");
	} else {
		std::string password = args[1];
		
		// Switch user mode from onboard to REGULAR
		// Implement state pattern ?
		if ( user.mode_isset(MODE_ONBOARD) && password == m_ctx.password ){
			user.set_mode(MODE_REGULAR);
		} else {
			user.update("bad password");
		}
	}
}
