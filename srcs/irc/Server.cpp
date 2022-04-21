/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:47 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 22:03:03 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

IRC::Server::Server(std::string const &host, std::string const &port, 
	std::string const &pass, bool bind_and_activate) : 
	m_host(host), 
	m_port(port),
	m_pass(pass),
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
		m_pass(other.m_pass),
		m_server(other.m_server), 
		m_selector(other.m_selector){ }

IRC::Server&
IRC::Server::operator=(Server const &other) {
	if ( this == &other )
		return *this;
	m_host = other.m_host;
	m_port = other.m_port;
	m_pass = other.m_pass;
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
	std::vector<File*>::iterator	it;
	ssize_t							bytes = 0;

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
				Socket *client = m_server->accept();

				std::cout << "New connection from " << client->storage() << std::endl;
				client->set_blocking(false);
				m_selector.add(client, Selector::READ | Selector::WRITE);
				api.connect(client);
			} else {
				if ( (bytes = socket->recv(buffer)) <= 0 ){
					// Connection shutdown
					if ( bytes == 0 ){
						std::cout << "Client has closed the connection" << std::endl;
					}
					api.disconnect(socket);
					m_selector.remove(socket);
					Socket::release(&socket);
				} else {
					// Received something
					file->push( buffer );

					// End of packets
					while ( file->available() ){
						api.process_request(socket, file->pop());
					}
				}
			}
		}
	}
}