/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:11:43 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/03 19:14:58 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCApi.hpp"
# include "CmdCtx.hpp"
# include "CmdFactory.hpp"
# include <iostream>

IRC::Api::Api(ConfigServer &config) : 
	m_users(),
	m_channels(),
	m_config(config),
	m_cmd_factory(new CmdFactory) { }

IRC::Api::Api(Api const &other) :
	m_users(other.m_users),
	m_channels(other.m_channels),
	m_config(other.m_config),
	m_cmd_factory(new CmdFactory) { }

IRC::Api&
IRC::Api::operator=(Api const &other){
	if ( &other == this )
		return *this;
	m_users = other.m_users;
	m_channels = other.m_channels;
	m_config = other.m_config;
	return *this;
}

IRC::Api::~Api() {
	delete m_cmd_factory;
}

void
IRC::Api::connect(Socket *socket) {
	std::cout << "Register user: " << socket->fd() << std::endl;
	m_users.create(socket);
}

void
IRC::Api::disconnect(Socket *socket){
	std::cout << "Unregister user: " << socket->fd() << std::endl;
	User *user = m_users.find(socket);

	if ( user != NULL )
		m_channels.remove_user(user);
	m_users.remove(socket);
}

IRC::Actions
IRC::Api::process_request(Socket *socket, std::string const &request) {
	ACmd *cmd;
	User *user;
	
	std::cout << "Received: " << request << std::endl;
	if ( socket != NULL ) {
		user = m_users.find(socket);

		if ( user != NULL ) {
			CmdCtx ctx(user, m_channels, m_users, m_config);

			cmd = m_cmd_factory->create_cmd(ctx, request);
			if ( cmd != NULL ) {
				Actions actions = cmd->execute();
				delete cmd;
				return actions;
			}
		}
	}
	return Actions::unique_idle();
}