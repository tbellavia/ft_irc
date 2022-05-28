/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPRIVMSG.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:36:57 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/29 00:00:46 by bbellavi         ###   ########.fr       */
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
			if ( mask::is_server_or_host_mask(*it) ){
				// Notify user mask
				std::cout << "Sending to mask!" << std::endl;

				this->send_to_user_mask_(*it, message, actions, reply);
			} else {
				std::cout << "Sending to channel!" << std::endl;
				this->send_to_channel_(*it, message, actions, reply);
			}
		} else {
			// Notify user
			std::cout << "Sending to user!" << std::endl;
			this->send_to_user_(*it, message, actions, reply);
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

void
IRC::CmdPRIVMSG::send_to_user_mask_(std::string const &mask, std::string const &message, Actions &actions, ReplyBuilder &reply) {
	// TODO: Change the target instead of sending the mask ?
	std::string reply_message = reply.reply_privmsg(message, mask);

	if ( !mask::is_valid(mask) )
		actions.push(Action::send(this->sender(), reply.error_wild_toplevel(mask)));
	else if ( mask::is_host_mask(mask) ){
		std::cout << "Sending to host mask!" << std::endl;
		actions.push(this->users().notify_host_mask(reply_message, mask, this->sender()));
	}
	// TODO: Manage server mask ?
}

void
IRC::CmdPRIVMSG::send_to_user_(std::string const &name, std::string const &message, Actions &actions, ReplyBuilder &reply) {
	User *target = this->users().select_unique(User::NickSelector(name));

	if ( target == NULL )
		actions.push(Action::send(this->sender(), reply.error_no_such_nick(name)));
	else
		actions.push(Action::send(target, reply.reply_privmsg(message, name)));
}
