/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:47 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/04 23:50:30 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

IRC::Server::Server(ConfigServer conf, bool bind_and_activate) : 
	m_config(conf),
	m_server(Socket::create_tcp_socket()), 
	m_selector()
{
	int enable = true;

	m_server->setsockopt(SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	m_server->set_blocking(false);
	if ( bind_and_activate ){
		this->bind();
		this->activate();
	}
}

IRC::Server::Server(IRC::Server const &other) :
		m_config(other.m_config),
		m_server(other.m_server), 
		m_selector(other.m_selector){ }

IRC::Server&
IRC::Server::operator=(Server const &other) {
	if ( this == &other )
		return *this;
	m_config = other.m_config;
	m_server = other.m_server;
	m_selector = other.m_selector;
	return *this;
}

void IRC::Server::activate() const {
	std::cout << "Listening on " << m_config.server_host << ":" << m_config.server_port << std::endl;
	m_server->listen(m_config.listen_max);
}

void IRC::Server::bind() const {
	m_server->bind(m_config.server_host, m_config.server_port);
}

void IRC::Server::serve_forever(IRC::Api &api) {
	std::pair<std::vector<File*>,
	std::vector<File*> >			ready;
	std::vector<File*>				readers;
	std::vector<File*>				writers;
	std::vector<File*>::iterator	it;
	ssize_t							bytes = 0;
	Actions							actions;

	m_selector.add(m_server, Selector::READ);
	while ( true ){
		ready = m_selector.select();
		readers = ready.first;
		writers = ready.second;

		for ( it = readers.begin() ; it != readers.end() ; ++it ){
			File		*file = *it;
			Socket		*socket = file->socket();
			std::string	buffer;

			if ( *socket == *m_server ){
				this->connect(api, m_server->accept());
			} else {
				if ( (bytes = socket->recv(buffer)) <= 0 ){
					// Connection shutdown
					if ( bytes == 0 ){
						std::cout << "Client has closed the connection" << std::endl;
					}
					this->disconnect(api, socket);
				} else {
					file->push( buffer );

					while ( file->available() ){
						actions = api.process_request(socket, file->pop());
						this->process_actions(api, actions);
						std::cout << "============================================" << std::endl;
					}
				}
			}
		}
	}
}

void
IRC::Server::process_actions(Api &api, Actions &actions){
	Action action;

	while ( !actions.empty() ){
		action = actions.pop();
		
		switch (action.event())
		{
			case Event::SEND:
				std::cout << "\tEvent send" << std::endl;
				this->sendall(action);
				break;
			case Event::DISCONNECT:
				std::cout << "\tEvent disconnect" << std::endl;
				this->disconnectall(api, action);
				break;
			case Event::BAN:
				std::cout << "\tEvent ban" << std::endl;
				break;
			case Event::IDLE:
				std::cout << "\tEvent idle" << std::endl;
				break;
		}
	}
}

void
IRC::Server::sendall(Action &action) {
	std::vector<Socket*> sockets = action.sockets();
	std::vector<Socket*>::iterator it = sockets.begin();

	for ( ; it != sockets.end() ; ++it ) {
		std::string response = net::ston(action.response());

		(*it)->send(response);
	}
}

void
IRC::Server::disconnect(Api &api, Socket *socket){
	if ( socket != NULL ){
		api.disconnect(socket);
		m_selector.remove(socket);
		Socket::release(&socket);
	}
}

void
IRC::Server::connect(Api &api, Socket *socket){
	if ( socket != NULL ){
		std::cout << "New connection from : " << socket->ip() << std::endl;
		socket->set_blocking(false);
		m_selector.add(socket, Selector::READ | Selector::WRITE);
		api.connect(socket);
	}
}

void
IRC::Server::disconnectall(Api &api, Action &action){
	std::vector<Socket*> sockets = action.sockets();
	
	for ( std::vector<Socket*>::iterator it = sockets.begin() ; it != sockets.end() ; ++it )
		this->disconnect(api, *it);
}