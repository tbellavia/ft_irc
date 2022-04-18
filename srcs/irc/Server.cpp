/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:47 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/18 17:49:50 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

IRC::Server::Server() : 
	m_host(),
	m_port(),
	m_server(),
	m_selector() { }

IRC::Server::Server(std::string const &host, std::string const &port, 
	std::string const &pass, bool bind_and_activate) : 
	m_host(host), 
	m_port(port), 
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

IRC::Server::Server(IRC::Server const &other)
	:	m_host(other.m_host), 
		m_port(other.m_port), 
		m_server(other.m_server), 
		m_selector(other.m_selector){ }

IRC::Server&
IRC::Server::operator=(Server const &other) {
	if ( this == &other )
		return *this;
	m_host = other.m_host;
	m_port = other.m_port;
	m_server = other.m_server;
	m_selector = other.m_selector;
	return *this;
}

void IRC::Server::activate() const {
	std::cout << "Listening on " << m_host << ":" << m_port << std::endl;
	m_server->listen(Server::LISTEN_MAX);
}

void IRC::Server::bind() const {
	m_server->bind(m_host, m_port);
}

void IRC::Server::serve_forever(IRC::Api &api) {
	std::pair<std::vector<File*>,
	std::vector<File*> >			ready;
	std::vector<File*>				readers;
	std::vector<File*>				writers;
	std::vector<File*>::iterator	select_it;
	ssize_t							bytes = 0;

	m_selector.add(m_server, Selector::READ);
	while ( true ){
		ready = m_selector.select();
		readers = ready.first;
		writers = ready.second;

		for ( select_it = readers.begin() ; select_it != readers.end() ; ++select_it ){
			File *select_file = *select_it;
			Socket *socket = select_file->socket();
			std::string buffer;

			if ( *socket == *m_server ){
				Socket *client = m_server->accept();

				std::cout << "New connection from " << client->storage() << std::endl;
				client->set_blocking(false);
				m_selector.add(client, Selector::READ | Selector::WRITE);
			} else {
				if ( (bytes = socket->recv(buffer)) <= 0 ){
					// Connection shutdown
					if ( bytes == 0 ){
						std::cout << "Client has closed the connection" << std::endl;
					}
					m_selector.remove(socket);
					Socket::release(&socket);
				} else {
					// Received something
					select_file->push( buffer );

					// End of packets
					while ( select_file->available() ){
						std::string request = select_file->pop();

						std::cout << "Request: " << request << std::endl;
					}
				}
			}
		}
	}
}

void
Server::process_request(IRC::Api &api, Socket *sender, std::string const &request) {
	(void)api;
	(void)sender;
	(void)request;
}