/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHO.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:08:34 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/26 16:02:55 by bbellavi         ###   ########.fr       */
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
		// TODO: If no mask, drop all users who aren't invisible
	} else {
		// Search in channel or for user 
		std::string mask = m_arguments[1];
		
		if ( Channel::is_channel_name(mask) ){
			Channel *channel = channels.find(mask);
			
			std::cout << "Mask: " << mask << std::endl;
			if ( channel != NULL ){
				Users::view_type users = channel->get_users();

				for ( ; users.first != users.second ; ++users.first )
					actions.push(Action::send(user, reply.reply_who_reply(channel, *users.first)));
				actions.push(Action::send(user, reply.reply_end_of_who(mask)));
				return actions;
			}
		}
	}
	return Actions::unique_idle();
}