/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPASS.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:00:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/04 19:23:52 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdPASS.hpp"
#include <iostream>

IRC::CmdPASS::CmdPASS(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "PASS") { }

IRC::CmdPASS::~CmdPASS() { }

/**
 * Pass
 * 
 * Pass password
 * The pass command takes a password and change the user state from
 * MODE_ONBOARD to MODE_REGULAR.
 * If a user is in a MODE_ONBOARD state, it can't do anything on
 * the server.
 */
IRC::Actions
IRC::CmdPASS::execute() {
	User *user = m_ctx.sender;
	ReplyBuilder reply(SERVER_NAME, user);
	std::vector<std::string> args = this->parse();
	
	std::cout << "CmdPASS: " << m_request << std::endl;
	if ( args.size() != Expected_args(1) ){
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	}
	std::string password = args[1];

	if ( user->connected() ){
		return Actions::unique_send(user, reply.error_already_registered());
	}
	else if ( !user->pass_accepted() && password == this->password() ){
		std::cout << "PASS ok!" << std::endl;
		user->set_mode(MODE_PASS_);
	}
	// If password is wrong, don't do anything
	return Actions::unique_idle();
}
