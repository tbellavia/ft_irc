/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:47 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/18 13:18:48 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

IRC::Server::Server(ConfigServer &conf, bool bind_and_activate) : 
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

IRC::Server::~Server() { }

void IRC::Server::activate() const {
	std::cout << "Listening on " << m_config.server_host << ":" << m_config.server_port << std::endl;
	m_server->listen(m_config.listen_max);
}

void IRC::Server::bind() const {
	m_server->bind(m_config.server_host, m_config.server_port);
}

void IRC::Server::serve_forever(IRC::Api &api) {
	std::set<File*>::iterator	it;
	ssize_t						bytes = 0;
	Actions						actions;

	m_selector.add(m_server, Selector::READ);
	while ( true ){
		this->select_();

		for ( it = m_readers.begin() ; it != m_readers.end() ; ++it ){
			File		*file = *it;
			Socket		*socket = file->socket();
			std::string	buffer;

			if ( *socket == *m_server ){
				this->connect_(api, m_server->accept());
			} else {
				if ( (bytes = socket->recv(buffer)) <= 0 ){
					// Connection shutdown
					if ( bytes == 0 ){
						std::cout << "Client has closed the connection" << std::endl;
					}
					this->disconnect_(api, socket);
				} else {
					file->push_request( buffer );

					/*
					 * Process all request from client (file), beware that
					 * this could block other clients if one has too many
					 * requests.
					*/
					while ( file->available_request() ){
						actions = api.process_request(socket, file->pop_request());
						this->process_actions_(api, actions);
						std::cout << "============================================" << std::endl;
					}
				}
			}
		}
		for ( it = m_writers.begin() ; it != m_writers.end() ; ++it ){
			File *file = *it;
			std::string response;
			int bytes = 0;

			if ( file->available_response() ){
				response = file->pop_response();
				bytes = file->socket()->send( response );
				file->seek_response(bytes);
			}
		}
		// TODO: Process other requests (DISCONNECT, BAN, ...)
	}
}

void
IRC::Server::process_actions_(Api &api, Actions &actions) {
	Action action;

	while ( !actions.empty() ){
		action = actions.pop();
		
		switch (action.event())
		{
			case Event::SEND:
				std::cout << "\tEvent send" << std::endl;
				this->sendall_(action);
				break;
			case Event::DISCONNECT:
				std::cout << "\tEvent disconnect" << std::endl;
				this->disconnectall_(api, action);
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
IRC::Server::send_(Socket *socket, std::string const &response) {
	if ( socket != NULL ){
		File *file = m_selector.find(socket);

		if ( file != NULL ){
			file->push_response( net::ston(response) );
		}
	}
}

void
IRC::Server::sendall_(Action &action) {
	std::vector<Socket*> sockets = action.sockets();
	std::vector<Socket*>::iterator it = sockets.begin();

	for ( ; it != sockets.end() ; ++it ) {
		this->send_(*it, action.response());
	}
}

void
IRC::Server::disconnect_(Api &api, Socket *socket){
	if ( socket != NULL ){
		File *file = m_selector.find(socket);

		// Remove File from writers to prevent using it in the writer loop.
		m_writers.erase(file);

		api.disconnect(socket);
		m_selector.remove(socket);
		Socket::release(&socket);
	}
}

void
IRC::Server::connect_(Api &api, Socket *socket){
	if ( socket != NULL ){
		std::cout << "New connection from : " << socket->ip() << std::endl;
		socket->set_blocking(false);
		m_selector.add(socket, Selector::READ | Selector::WRITE);
		api.connect(socket);
	}
}

void
IRC::Server::disconnectall_(Api &api, Action &action){
	std::vector<Socket*> sockets = action.sockets();
	
	for ( std::vector<Socket*>::iterator it = sockets.begin() ; it != sockets.end() ; ++it )
		this->disconnect_(api, *it);
}

void
IRC::Server::select_() {
	m_ready = m_selector.select();
	m_readers = m_ready.first;
	m_writers = m_ready.second;
}