/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNAMES.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:07:09 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/10 15:15:10 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdNAMES.hpp"

IRC::CmdNAMES::CmdNAMES(CmdCtx &ctx, std::string const &request) 
	: ACmd(ctx, request, "NAMES") {}

IRC::CmdNAMES::~CmdNAMES() { }

IRC::Actions
IRC::CmdNAMES::execute() {
	User			*user = this->sender();
	ReplyBuilder	reply(this->server_name(), user);
	Actions			actions;
	Channel			*channel;

	if ( !user->connected() )
		return Actions::unique_idle();
	if ( m_arguments.size() == Expected_args(0) )
		return Actions::unique_send(user, reply.reply_end_of_names("*"));
	std::vector<std::string> names = ft::split(m_arguments[1], ",");
	std::vector<std::string>::iterator it = names.begin();

	for ( ; it != names.end() ; ++it ){
		channel = this->channels().find(*it);
		
		if ( channel != NULL ){
			if ( channel->is_user(user) && (!channel->is_private() || !channel->is_secret())){
				actions.push(Action::send(user, reply.reply_name_reply(*channel)));
			}
		}
		actions.push(Action::send(user, reply.reply_end_of_names(*it)));
	}
	return actions;
}