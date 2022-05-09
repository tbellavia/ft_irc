/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:11:43 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:16:09 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCApi.hpp"
# include "CmdCtx.hpp"
# include "CmdFactory.hpp"
# include <iostream>

IRC::Api::Api(std::string const &password) : 
	m_users(),
	m_channels(),
	m_password(password),
	m_cmd_factory(new CmdFactory) { }

IRC::Api::Api(Api const &copy):
	m_users(copy.m_users),
	m_channels(copy.m_channels),
	m_password(copy.m_password),
	m_cmd_factory(copy.m_cmd_factory) { }

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
			CmdCtx ctx(user, m_channels, m_users, m_password);

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

IRC::Api &IRC::Api::operator=(Api const &rhs) {
	if (this == &rhs)
		return *this;

	m_users = rhs.m_users;
	m_channels = rhs.m_channels;
	m_password = rhs.m_password;
	m_cmd_factory = rhs.m_cmd_factory;
	return *this;
}