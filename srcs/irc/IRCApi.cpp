/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:11:43 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/13 17:24:22 by lperson-         ###   ########.fr       */
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
	m_cmd_factory(new CmdFactory) {
	m_register_exceptions_cmds.insert("PASS");
	m_register_exceptions_cmds.insert("NICK");
	m_register_exceptions_cmds.insert("USER");
	m_register_exceptions_cmds.insert("QUIT");
}

IRC::Api::Api(Api const &other) :
	m_users(other.m_users),
	m_channels(other.m_channels),
	m_config(other.m_config),
	m_register_exceptions_cmds(other.m_register_exceptions_cmds),
	m_cmd_factory(new CmdFactory) { }

IRC::Api&
IRC::Api::operator=(Api const &other){
	if ( &other == this )
		return *this;
	m_users = other.m_users;
	m_channels = other.m_channels;
	m_register_exceptions_cmds = other.m_register_exceptions_cmds;
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
			std::vector<std::string> const cmd_name = ft::split_one(request);
			ReplyBuilder reply(m_config.server_name, user);
			if (
				m_register_exceptions_cmds.find(cmd_name[0]) ==
				m_register_exceptions_cmds.end() && !user->connection_complete()
			) {
				return Actions::unique_send(user, reply.error_not_registered());
			}

			if (cmd_name[0] == "SUMMON")
				return Actions::unique_send(
					user, reply.error_summon_disabled()
				);
			if (cmd_name[0] == "USERS")
				return Actions::unique_send(
					user, reply.error_users_disabled()
				);

			CmdCtx ctx(user, m_channels, m_users, m_config);
			cmd = m_cmd_factory->create_cmd(cmd_name[0], ctx, request);
			if ( cmd != NULL ) {
				Actions actions = cmd->execute();
				delete cmd;
				return actions;
			}
		}
	}
	return Actions::unique_idle();
}