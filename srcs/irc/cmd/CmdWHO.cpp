/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHO.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:08:34 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/19 13:02:08 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdWHO.hpp"
#include <iostream>

IRC::CmdWHO::CmdWHO(CmdCtx &ctx, std::string const &request) :
	ACmd(ctx, request, "WHO") { }

IRC::CmdWHO::~CmdWHO() { }

IRC::Actions
IRC::CmdWHO::execute() {
	User *user = this->sender();
	Channels &channels = this->channels();
	ReplyBuilder reply(this->server_name(), user);
	Actions actions;

	if ( m_arguments.size() == Expected_args(0) ){
		// If no mask, drop all users who aren't invisible
	} else {
		// Search in channel or for user 
		std::string mask = m_arguments[1];
		
		if ( Channel::is_channel_name(mask) ){
			Channel *channel = channels.find(mask);
			
			std::cout << "Mask: " << mask << std::endl;
			if ( channel != NULL ){
				Users::view_type users = channel->get_users();

				for ( ; users.first != users.second ; ++users.first ){
					std::string response = reply.reply_who_reply(channel, *users.first);

					std::cout << "WHO: " << response << std::endl;
					actions.push(Action::send(user, response));
				}
				actions.push(Action::send(user, reply.reply_end_of_who(mask)));
				return actions;
			}
		}
	}
	return Actions::unique_idle();
}