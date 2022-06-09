/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:53:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/09 11:00:18 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdJOIN.hpp"
#include "NumericReplies.hpp"
#include <iostream>

IRC::CmdJOIN::CmdJOIN(CmdCtx &ctx, std::string const &request) :
	ACmd(ctx, request, "JOIN") { }

IRC::CmdJOIN::~CmdJOIN() { }

IRC::Actions
IRC::CmdJOIN::execute() {
	User *user = m_ctx.sender;
	Channels &channels = m_ctx.channels;
	ReplyBuilder reply(this->server_name(), this->sender());

	std::cout << "CmdJOIN: " << std::endl;
	// Not enough arguments
	if ( m_arguments.size() == 1 || m_arguments.size() > Expected_args(2) ){
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	}
	std::vector<std::string> m_arguments_chan = ft::split(m_arguments[1], ",");
	std::vector<std::string> m_arguments_keys;

	if ( m_arguments.size() == Expected_args(2) ){
		m_arguments_keys = ft::split(m_arguments[2], ",");
	}
	Actions actions;
	std::vector<std::string>::iterator chan_it = m_arguments_chan.begin();
	std::vector<std::string>::iterator keys_it = m_arguments_keys.begin();

	while ( chan_it != m_arguments_chan.end() ){
		std::string name = *chan_it;
		std::string key;

		if ( keys_it != m_arguments_keys.end() ){
			key = *keys_it;
			++keys_it;
		}

		if ( Channel::is_valid_name(name) ){
			Channel *channel = channels.find(name);

			if ( channel != NULL ) {
				if ( channel->is_banned_user(user) )
					return Actions::unique_send(user, reply.error_banned_from_channel(name));
				if ( channel->is_private() && !channel->equal_key(key) )
					return Actions::unique_send(user, reply.error_bad_channel_key(name));
				if ( channel->is_invite() && !channel->is_invited_user(user) )
					return Actions::unique_send(user, reply.error_invite_only_channel(name));
				channel->subscribe(user);

				// Delete invitation once user has joined if it was invited
				if (channel->is_invited_user(user))
					channel->uninviteUser(user);
				this->channel_joined_reply(reply, actions, *channel);
				std::cout << "Join channel: " << name << std::endl;
			} else {
				// Create channel
				Channel new_channel(name, user);
				
				std::cout << "Created channel: " << name << std::endl;
				new_channel.subscribe(user);
				channels.add(new_channel);
				this->channel_created_reply(reply, actions, new_channel);
			}
		} else {
			return Actions::unique_send(user, reply.error_no_such_channel(name));
		}
		++chan_it;
	}
	return actions;
}

void
IRC::CmdJOIN::channel_created_reply(ReplyBuilder &reply, Actions &actions, Channel &channel){
	std::string name = channel.get_name();
	
	// JOIN response
	actions.push(Action::send(this->sender(), reply.reply_join(channel.get_name())));
	// RPL_NAMEREPLY
	actions.push(Action::send(this->sender(), reply.reply_name_reply(channel)));
	// RPL_ENDOFNAMES
	actions.push(Action::send(this->sender(), reply.reply_end_of_names(name)));
}

void
IRC::CmdJOIN::channel_joined_reply(ReplyBuilder &reply, Actions &actions, Channel &channel){
	std::string name = channel.get_name();
	
	// JOIN response
	actions.push(Action::send(this->sender(), reply.reply_join(channel.get_name())));
	// RPL_NAMEREPLY
	actions.push(Action::send(this->sender(), reply.reply_name_reply(channel)));
	// RPL_ENDOFNAMES
	actions.push(Action::send(this->sender(), reply.reply_end_of_names(name)));
	// RPL_TOPIC
	std::string const &topic = channel.get_topic();
	if ( topic.empty() )
		actions.push(Action::send(this->sender(), reply.reply_notopic(name)));
	else
		actions.push(Action::send(this->sender(), reply.reply_topic(name, channel.get_topic())));
}
