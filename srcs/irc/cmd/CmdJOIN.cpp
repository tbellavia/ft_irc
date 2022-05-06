/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:53:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 00:50:01 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdJOIN.hpp"
#include <iostream>

IRC::CmdJOIN::CmdJOIN(CmdCtx &ctx, std::string const &request) :
	ACmd(ctx, request, "JOIN") { }

IRC::CmdJOIN::~CmdJOIN() { }

IRC::Actions
IRC::CmdJOIN::execute() {
	User *user = m_ctx.sender;
	Channels &channels = m_ctx.channels;
	std::vector<std::string> args = this->parse();
	ReplyBuilder reply(this->server_name(), user);

	std::cout << "CmdJOIN: " << std::endl;
	if ( args.size() == 1 || args.size() > Expected_args(2) ){
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	}
	std::vector<std::string> args_chan = ft::split(args[1], ",");
	std::vector<std::string> args_keys;

	if ( args.size() == Expected_args(2) ){
		args_keys = ft::split(args[2], ",");
	}
	// TODO: Test if creating a channel with a password

	std::vector<std::string>::iterator chan_it = args_chan.begin();
	std::vector<std::string>::iterator keys_it = args_keys.begin();
	while ( chan_it != args_chan.end() ){
		std::string name = *chan_it;
		std::string key;

		if ( keys_it != args_keys.end() ){
			key = *keys_it;
			++keys_it;
		}

		if ( Channel::is_valid(name) ){
			if ( channels.has(name) )
				this->join_channel(name, key);
			else
				this->create_channel(name, key);
		}

		++chan_it;
	}
	return Actions::unique_idle();
}

IRC::Actions
IRC::CmdJOIN::join_channel(std::string const &name, std::string const &pass) {
	// Channel &channel = 
}

IRC::Actions
IRC::CmdJOIN::create_channel(std::string const &name, std::string const &pass) {
	Channel channel(name, pass);

	printf("Channel does not exist, creating it (%s)\n", name.c_str());
	m_ctx.channels.add(channel);
	return Actions::unique_idle();
}