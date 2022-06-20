/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHO.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:08:34 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/20 13:10:14 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdWHO.hpp"
#include "Masks.hpp"
#include <iostream>

IRC::CmdWHO::CmdWHO(CmdCtx &ctx, std::string const &request) :
	ACmd(ctx, request, "WHO") { }

IRC::CmdWHO::~CmdWHO() { }

IRC::Actions
IRC::CmdWHO::execute() {
	User			*user = this->sender();
	ReplyBuilder	reply(this->server_name(), user);
	Actions			actions;
	bool			op_only = false;

	if ( m_arguments.size() == Expected_args(0) )
		this->drop_all_(actions, reply);
	if ( m_arguments.size() > Expected_args(2) )
		return Actions::unique_idle();
	if ( m_arguments.size() == Expected_args(2) )
		op_only = (m_arguments[2] == "o");
	std::string mask = m_arguments[1];

	if ( mask::is_mask(mask) )
		this->drop_by_mask_(mask, op_only, actions, reply);
	else
		this->drop_by_channel_(mask, op_only, actions, reply);
	return actions;
}

void
IRC::CmdWHO::drop_all_(Actions &actions, ReplyBuilder &reply) {
	User *sender = this->sender();

	Users::view_type view = this->users().get_view();
	std::cout << "WHO: DROP ALL" << std::endl;
	if ( view.first == view.second )
		return ;
	for ( ; view.first != view.second ; ++view.first ){
		User *user = *view.first;

		if ( !user->is_invisible() ) {
			actions.push(Action::send(sender, reply.reply_who_reply(user)));
		}
	}
	actions.push(Action::send(sender, reply.reply_end_of_who()));
}

void
IRC::CmdWHO::drop_by_mask_(std::string const &mask, bool op_only, Actions &actions, ReplyBuilder &reply) {
	User *sender = this->sender();
	Users::view_type view = this->users().get_view();
	Channel *channel;

	std::cout << "WHO: DROP BY MASK" << std::endl;
	for ( ; view.first != view.second ; ++view.first ){
		// host, server, realname, nickname
		User *user = *view.first;

		if ( !user->mask_match(mask::construct_mask(mask)) )
			continue;
		channel = this->channels().find_by_user(user);
		if ( (!op_only && !user->is_invisible()) || (op_only && !user->is_invisible() && user->is_server_operator()) )
			actions.push(Action::send(sender, reply.reply_who_reply(user, channel)));
	}
	actions.push(Action::send(sender, reply.reply_end_of_who(mask)));
}

void
IRC::CmdWHO::drop_by_channel_(std::string const &name, bool op_only, Actions &actions, ReplyBuilder &reply) {
	Channel				*channel = this->channels().find(name);
	User				*sender = this->sender();
	User				*user;
	Users::view_type	view;

	std::cout << "WHO: DROP BY CHANNEL" << std::endl;
	if ( channel == NULL )
		return ;
	view = channel->get_users();
	for ( ; view.first != view.second ; ++view.first ){
		user = *view.first;

		if ( !op_only || (op_only && (channel->is_operator_user(user) || user->is_server_operator())) )
			actions.push(Action::send(sender, reply.reply_who_reply(user, channel)));
	}
	actions.push(Action::send(sender, reply.reply_end_of_who(channel)));
}