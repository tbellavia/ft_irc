/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPRIVMSG.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:36:57 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/27 22:48:34 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdPRIVMSG.hpp"
#include "Masks.hpp"
#include <iostream>

IRC::CmdPRIVMSG::CmdPRIVMSG(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "PRIVMSG") { }

IRC::CmdPRIVMSG::~CmdPRIVMSG() { }

IRC::Actions
IRC::CmdPRIVMSG::execute() {
	User *user = this->sender();
	ReplyBuilder reply(this->server_name(), user);
	Actions actions;
	// Channel *channel;

	if ( !user->connected() )
		return Actions::unique_idle();
	// ALGORITHM PRIVMSG :
	// 
	// 1. Check if sufficient arguments is given
	// 2. While there are targets
	// 	2.a. If <target> is channel
	//		2.a.a. Send message to all subscribers of channel
	// 	2.b. If <target> is mask or user
	// 		2.b.a. Check if mask is correct
	// 		2.b.c. Send to all user matching the mask
	if ( m_arguments.size() < Expected_args(1) )
		return Actions::unique_send(user, reply.error_no_recipient(m_name));
	if ( m_arguments.size() < Expected_args(2) )
		return Actions::unique_send(user, reply.error_no_text_to_send());
	std::vector<std::string> targets = ft::split(m_arguments[1], ",");
	std::vector<std::string>::iterator it = targets.begin();
	std::string message = ft::popfirst(m_arguments[2]);

	for ( ; it != targets.end() ; ++it ){
		// Does the command continue if user or channel does not exists ? Yes
		if ( Channel::is_channel_name(*it) ){
			this->send_to_channel_(*it, message, actions, reply);
		} else {
			
		}
	}
	std::cout << "Arguments: ";
	ft::debug_log_args(targets.begin(), targets.end(), std::cout);
	std::cout << std::endl;
	return actions;
}

void
IRC::CmdPRIVMSG::send_to_channel_(std::string const &name, std::string const &message, Actions &actions, ReplyBuilder &reply) {
	Channel *channel = this->channels().find(name);

	if ( channel == NULL ){
		// No such nick if channel not found ?
		actions.push(Action::send(this->sender(), reply.error_no_such_nick(name)));
	} else {
		actions.push(channel->notify(
			reply.reply_privmsg(message, name), 
			this->sender())
		);
	}
}
