/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:47 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:52:04 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

IRC::Server::Server(std::string const &host, std::string const &port, bool bind_and_activate) : 
	m_host(host), 
	m_port(port), 
	m_server(Socket::create_tcp_socket()), 
	m_selector(),
	m_channels()
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
		m_selector(other.m_selector),
		m_channels(other.m_channels) { }

IRC::Server&
IRC::Server::operator=(Server const &other) {
	if ( this == &other )
		return *this;
	m_host = other.m_host;
	m_port = other.m_port;
	m_server = other.m_server;
	m_selector = other.m_selector;
	m_channels = other.m_channels;
	return *this;
}

void IRC::Server::activate() const {
	std::cout << "Listening on " << m_host << ":" << m_port << std::endl;
	m_server->listen(Server::LISTEN_MAX);
}

void IRC::Server::bind() const {
	m_server->bind(m_host, m_port);
}

void IRC::Server::serve_forever() {
	std::pair<std::vector<SelectorValue*>,
	std::vector<SelectorValue*> >			ready;
	std::vector<SelectorValue*>				readers;
	std::vector<SelectorValue*>				writers;
	std::vector<SelectorValue*>::iterator	select_it;
	ssize_t									bytes = 0;

	m_selector.add(m_server, Selector::READ);
	while ( true ){
		ready = m_selector.select();
		readers = ready.first;
		writers = ready.second;

		for ( select_it = readers.begin() ; select_it != readers.end() ; ++select_it ){
			SelectorValue	*select_value = *select_it;
			Socket			*socket = select_value->socket();
			std::string		buffer;

			if ( *socket == *m_server ){
				Socket *client = m_server->accept();

				std::cout << "New connection from " << client->storage() << std::endl;
				client->set_blocking(false);
				m_selector.add(client, Selector::READ | Selector::WRITE);
				// Create and add new user
				m_users.insert(std::make_pair(client, new User(client)));
			} else {
				std::map<Socket*, User*>::iterator found = m_users.find(socket);
				User *user = found->second;

				if ( (bytes = socket->recv(buffer)) <= 0 ){
					// Connection shutdown
					if ( bytes == 0 ){
						std::cout << "Client has closed the connection" << std::endl;
					}
					// Errors 
					m_selector.remove(socket);

					delete user;
					m_users.erase(found);

					Socket::release(&socket);
				} else {
					// Received something
					select_value->append( buffer );

					// End of packets
					if ( select_value->has_terminator() ){
						std::string raw = select_value->flush();
						std::vector<std::string> args = ft::split(raw, " ");
						std::string cmd = args[0];

						if ( cmd == "NICK" ){
							user->set_pseudo(args[1]);
						}
						else if ( cmd == "CHANNEL" ) {
							m_channels.add(args[1]);
						}
						std::cout << "Command: " << cmd << std::endl;
					}
				}
			}
		}
	}
}