/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdQUIT.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:57:08 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 23:32:24 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdQUIT.hpp"
#include <iostream>

IRC::CmdQUIT::CmdQUIT(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request) { }

IRC::CmdQUIT::~CmdQUIT() { }

/**
 * QUIT
 * 
 * QUIT [<Quit message>]
 */
IRC::Actions
IRC::CmdQUIT::execute() {
	Actions actions;
	User *user = m_ctx.sender;
	std::vector<std::string> args = ft::split(m_request, ":");
	
	std::cout << "CmdQUIT" << std::endl;
	if ( args.size() >= 2 ){
		std::string message = args[1];
		
		actions.push(Action::send(user, message));
	}
	actions.push(Action::disconnect(user));
	return actions;
}