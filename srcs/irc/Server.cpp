/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:47 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/08 10:33:05 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

IRC::Server::Server(ConfigServer &conf, Api &api, bool bind_and_activate) : 
	m_config(conf),
	m_server(Socket::create_tcp_socket()), 
	m_selector(),
	m_ready(),
	m_writers(),
	m_readers(),
	m_api(api)
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
		m_selector(other.m_selector),
		m_api(other.m_api) { }

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

void IRC::Server::serve_forever() {
	m_selector.add(m_server, Selector::READ);
	m_config.update_creation_date();

	while ( true ){
		this->select_();

		this->read_requests_();
		this->write_responses_();
		
		// TODO: Process other requests (DISCONNECT, BAN, ...)
		this->finish_requests_();
	}
}

void
IRC::Server::read_requests_() {
	std::set<File*>::iterator	it;
	std::set<File*>::iterator	tmp;
	Actions						actions;
	ssize_t						bytes = 0;

	for ( it = m_readers.begin() ; it != m_readers.end() ; ++it ){
		File		*file = *it;
		Socket		*socket = file->socket();
		std::string	buffer;

		if ( *socket == *m_server ){
			this->connect_socket_(m_server->accept());
		} else {
			if ( (bytes = socket->recv(buffer)) <= 0 ){
				// Connection shutdown
				if ( bytes == 0 ){
					std::cout << "Client has closed the connection" << std::endl;
				}
				// Remove File from writers to prevent using it in the writer loop.
				m_writers.erase( file );
				this->disconnect_socket_( socket );
			} else {
				file->push_request( buffer );

				/*
				* Process all request from client (file), beware that
				* this could block other clients if one has too many
				* requests.
				*/
				while ( file->available_request() ){
					actions = m_api.process_request(socket, file->pop_request());
					this->handle_actions_(actions);
					std::cout << "============================================" << std::endl;
				}
			}
		}
	}
}

void
IRC::Server::write_responses_() {
	std::set<File*>::iterator	it;
	ssize_t						bytes = 0;
	
	for ( it = m_writers.begin() ; it != m_writers.end() ; ++it ){
		File *file = *it;
		std::string response;

		if ( file->available_response() ){
			response = file->pop_response();
			bytes = file->socket()->send( response );
			file->seek_response(bytes);
		}
	}
}

void
IRC::Server::finish_requests_() {
	std::map<int, File*> const &entries = m_selector.get_entries();
	std::map<int, File*>::const_iterator it;

	for ( it = entries.begin() ; it != entries.end() ; ++it ){
		File *file = it->second;
		Socket *socket = file->socket();

		if ( file->isset_event(Selector::DISCONNECT) && !file->available_response() ){
			// WARN: this line is super important, do not touch !!!
			++it;
			this->disconnect_socket_(socket);
		}
	}
}

/**
 * Handle actions
 * 
 * Handle actions and route it to the right service. 
 */
void
IRC::Server::handle_actions_(Actions &actions) {
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
				this->disconnectall_(action);
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

/**
 * Push send
 * 
 * Push a send request into the associated File object.
 * The request is later processed by the server when the
 * socket is available in writing mode.
 */
void
IRC::Server::push_send_(Socket *socket, std::string const &response) {
	if ( socket != NULL ){
		File *file = m_selector.find(socket);

		if ( file != NULL ){
			std::cout << "Response: '" << response << "'" << std::endl;
			file->push_response( net::ston(response) );
		}
	}
}

/**
 * Sendall
 * 
 * Push send request into all sockets File.
 */
void
IRC::Server::sendall_(Action &action) {
	std::vector<Socket*> sockets = action.sockets();
	std::vector<Socket*>::iterator it = sockets.begin();

	for ( ; it != sockets.end() ; ++it ) {
		this->push_send_(*it, action.response());
	}
}

/**
 * Connect socket
 * 
 * Connect a socket to the underlying services :
 * 	- IRC::Api
 * 	- Selector
 */
void
IRC::Server::connect_socket_(Socket *socket){
	if ( socket != NULL ){
		std::cout << "New connection from : " << socket->ip() << std::endl;
		socket->set_blocking(false);
		m_selector.add(socket, Selector::READ | Selector::WRITE);
		m_api.connect(socket);
	}
}

/**
 * Push disconnect
 * 
 * Push a disconnect event into File events.
 */
void
IRC::Server::push_disconnect_(Socket *socket){
	if ( socket != NULL ){
		File *file = m_selector.find(socket);

		if ( file != NULL )
			file->set_event(Selector::DISCONNECT);
		m_selector.unset(socket, Selector::READ);
	}
}

/**
 * Disconnect socket
 * 
 * Disconnect a socket from the underlying services :
 * 	- IRC::Api
 * 	- Selector
 */
void
IRC::Server::disconnect_socket_(Socket *socket) {
	if ( socket != NULL ){
		m_api.disconnect(socket);
		m_selector.remove(socket);
		Socket::release(&socket);
	}
}


/**
 * Disconnect all
 * 
 * Push disconnect event into all File object associated to sockets.
 */
void
IRC::Server::disconnectall_(Action &action){
	std::vector<Socket*> sockets = action.sockets();
	
	for ( std::vector<Socket*>::iterator it = sockets.begin() ; it != sockets.end() ; ++it )
		this->push_disconnect_(*it);
}

/**
 * Select
 * 
 * Select_ wrap Selector::select method.
 */
void
IRC::Server::select_() {
	m_ready = m_selector.select();
	m_readers = m_ready.first;
	m_writers = m_ready.second;
}