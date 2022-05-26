/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPRIVMSG.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:36:57 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/26 16:33:31 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdPRIVMSG.hpp"
#include <iostream>

IRC::CmdPRIVMSG::CmdPRIVMSG(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "PRIVMSG") { }

IRC::CmdPRIVMSG::~CmdPRIVMSG() { }

IRC::Actions
IRC::CmdPRIVMSG::execute() {
	User *user = this->sender();
	ReplyBuilder reply(this->server_name(), user);
	Channel *channel;

	
	if ( !user->connected() )
		return Actions::unique_idle();
	std::string name = m_arguments[1];
	std::string message = ft::popfirst(m_arguments[2]);

	std::cout << "Name: " << name << std::endl;
	std::cout << "Message: " << message << std::endl;
	channel = this->channels().find(name);
	if ( channel == NULL )
		return Actions::unique_idle();
	return channel->notify(reply.reply_privmsg(message, name), this->sender());
}