/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:11:43 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 15:30:27 by bbellavi         ###   ########.fr       */
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

void
IRC::Api::process_request(Socket *socket, std::string const &request) {
	ACmd *cmd;
	User *user;
	
	std::cout << "Received: " << request << std::endl;
	if ( socket != NULL ) {
		user = m_users.find(socket);

		if ( user != NULL ) {
			CmdCtx ctx(*user, m_channels, m_users, m_password);

			cmd = m_cmd_factory->create_cmd(ctx, request);
			if ( cmd != NULL ) {
				cmd->execute();
				delete cmd;
			}
		}
	}
}