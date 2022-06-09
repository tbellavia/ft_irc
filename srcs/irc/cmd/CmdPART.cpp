/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPART.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:00:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/09 11:54:31 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdPART.hpp"
#include <iostream>

IRC::CmdPART::CmdPART(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "PART") { }

IRC::CmdPART::~CmdPART() { }

IRC::Actions
IRC::CmdPART::execute() {
	User			*sender = this->sender();
	ReplyBuilder	reply(this->server_name(), sender);
	Actions			actions;
	std::string		message;
	
	if ( m_arguments.size() == Expected_args(0) )
		return Actions::unique_send(sender, reply.error_need_more_params(m_name));
	if ( m_arguments.size() == Expected_args(2) )
		message = ft::popfirst(m_arguments[2]);
	else
		message = "Leaving";
	std::vector<std::string> targets = ft::split(m_arguments[1], ",");
	std::vector<std::string>::iterator it = targets.begin();

	for ( ; it != targets.end() ; ++it ){
		Channel *channel = this->channels().find(*it);

		if ( channel != NULL ){
			if ( channel->is_user(sender) ){
				actions.push(
					channel->notify(
						reply.reply_part(channel->get_name(), message)
					)
				);
				channel->unsubscribe(sender);
			} else {
				actions.push(Action::send(sender, reply.error_not_on_channel(*it)));
			}
		}
		else {
			actions.push(Action::send(sender, reply.error_no_such_channel(*it)));
		}
	}
	return actions;
}