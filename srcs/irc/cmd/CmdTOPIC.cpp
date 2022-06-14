/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTOPIC.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:00:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/09 12:25:02 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdTOPIC.hpp"

IRC::CmdTOPIC::CmdTOPIC(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "TOPIC") { }

IRC::CmdTOPIC::~CmdTOPIC() { }

IRC::Actions
IRC::CmdTOPIC::execute() {
	User			*user = this->sender();
	ReplyBuilder	reply(this->server_name(), user);
	Actions			actions;

	if ( !user->connected() )
		return Actions::unique_idle();
	if ( m_arguments.size() < Expected_args(1) || m_arguments.size() > Expected_args(2))
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	std::string name = m_arguments[1];
	Channel *channel = this->channels().find(name);
	
	if ( channel == NULL )
		return Actions::unique_send(user, reply.error_no_such_channel(name));
	if ( !channel->is_user(user) )
		return Actions::unique_send(user, reply.error_not_on_channel(name));
	if ( m_arguments.size() == Expected_args(1) ){
		// Get topic
		std::string const &topic = channel->get_topic();

		if ( topic.empty() )
			return Actions::unique_send(user, reply.reply_notopic(name));
		return Actions::unique_send(user, reply.reply_topic(name, topic));
	}
	// Set topic
	if (
		channel->get_mode() & CHAN_MODE_TOPIC_BY_OP &&
		!channel->is_operator_user(user)
	)
		return Actions::unique_send(user, reply.error_chan_o_privs_needed(name));
	std::string new_topic = m_arguments[2];

	channel->set_topic(new_topic);
	return channel->notify(reply.reply_new_topic(
		this->sender(), channel->get_name(), new_topic
	));
}