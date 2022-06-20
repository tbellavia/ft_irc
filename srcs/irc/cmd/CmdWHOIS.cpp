/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHOIS.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:58:02 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/19 23:25:44 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CmdWHOIS.hpp"
# include "Masks.hpp"
# include <iostream>

IRC::CmdWHOIS::CmdWHOIS(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "WHOIS") { }

IRC::CmdWHOIS::~CmdWHOIS() { }

IRC::Actions
IRC::CmdWHOIS::execute() {
	User						*user = this->sender();
	ReplyBuilder				reply(this->server_name(), user);
	Actions						actions;
	std::vector<std::string>	nickmasks;

	if ( m_arguments.size() < Expected_args(1) )
		return Actions::unique_send(user, reply.error_no_nickname_given());
	if ( m_arguments.size() == Expected_args(1) )
		nickmasks = ft::split(m_arguments[1], ",");
	else
		nickmasks = ft::split(m_arguments[2], ",");

	std::vector<std::string>::iterator it = nickmasks.begin();
	for ( ; it != nickmasks.end() ; ++it ){
		if ( mask::is_mask(*it) )
			whois_mask(*it, actions, reply);
		else
			whois(*it, actions, reply);
	}
	return actions;
}

void
IRC::CmdWHOIS::single_whois(User *target, Actions &actions, ReplyBuilder &reply){
	if ( target == NULL )
		return;
	std::vector<Channel*> sub_channels = this->channels().get_channels_by_user(target);

	actions.push(Action::send(this->sender(), reply.reply_whois_user(target)));
	actions.push(Action::send(this->sender(), reply.reply_whois_channels(target, sub_channels)));
	if ( target->is_server_operator() )
		actions.push(Action::send(this->sender(), reply.reply_whois_operator(target)));
	actions.push(Action::send(this->sender(), reply.reply_whois_server(target, this->server_name(), "Pretty good IRC Server")));
	actions.push(Action::send(this->sender(), reply.reply_end_of_whois(target->get_nickname())));
}

void
IRC::CmdWHOIS::whois(std::string const &nickname, Actions &actions, ReplyBuilder &reply) 
{
	User *target = this->users().unique_find_by_nickmask(nickname);

	if ( target == NULL )
		actions.push(Action::send(this->sender(), reply.error_no_such_nick(nickname)));
	else
		single_whois(target, actions, reply);
}

void
IRC::CmdWHOIS::whois_mask(std::string const &nickmask, Actions &actions, ReplyBuilder &reply) {
	Users targets = this->users().find_by_nickmask(nickmask);

	if ( targets.empty() )
		actions.push(Action::send(this->sender(), reply.error_no_such_nick(nickmask)));
	else {
		Users::view_type view = targets.get_view();

		for ( ; view.first != view.second ;  ++view.first ) {
			single_whois(*view.first, actions, reply);
		}
	}
}