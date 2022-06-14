/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdQUIT.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:57:08 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/15 00:14:16 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdQUIT.hpp"
#include <iostream>

IRC::CmdQUIT::CmdQUIT(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "QUIT") { }

IRC::CmdQUIT::~CmdQUIT() { }

/**
 * QUIT
 * 
 * QUIT [<Quit message>]
 */
IRC::Actions
IRC::CmdQUIT::execute() {
	Actions			actions;
	User			*sender = m_ctx.sender;
	ReplyBuilder	reply(this->server_name(), sender);
	std::string		message = "Leaving";
	
	// Notify all channels where sender is present
	if ( m_arguments.size() == Expected_args(1))
		message = m_arguments[1];
	message = reply.reply_quit(message);
	actions = this->channels().notify_by_user(sender, message);
	actions.push(Action::disconnect(sender));
	return actions;
}
