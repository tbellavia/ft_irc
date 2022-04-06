/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/04/06 18:33:33 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <algorithm>
#include "../include/Socket.hpp"
#include "../include/Selector.hpp"
#include "../include/Network.hpp"

int main(int argc, char *argv[])
{
	if ( argc != 3 ){
		std::cerr << "usage: server host port" << std::endl;
		return EXIT_FAILURE;
	}
	std::pair<Selector::ready_type, Selector::ready_type>	ready;
	Selector::ready_type									ready_readers;
	Selector::ready_type									ready_writers;
	std::string 											host = argv[1];
	std::string 											port = argv[2];
	Socket													*server = Socket::create_tcp_socket();
	Selector												selector;
	int														yes = 1;

	// Configure and setup server
	server->setsockopt(SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	server->bind(host, port);
	server->listen(10);

	std::cout << "Listening on " << host << ":" << port << std::endl;

	// Add server to selector
	selector.add(server, Selector::READ);

	while ( true ){
		ready = selector.select();
		ready_readers = ready.first;
		ready_writers = ready.second;

		std::for_each(ready_readers.begin(), ready_readers.end(), 
			[&](Socket *current){
				std::string buffer;

				if ( *current == *server ){
					Socket *client = server->accept();

					std::cout << "New connection from " << client->storage() << std::endl;

					std::for_each(ready_writers.begin(), ready_writers.end(), [&](Socket *client){
						client->send("A new user has join the server.\n");
					});
					
					selector.add(client, Selector::READ | Selector::WRITE);
				} else {
					ssize_t bytes = 0;

					if ( (bytes = current->recv(buffer)) <= 0 ){
						// Connection has been closed, cleaning and removing
						if ( bytes == 0 ){
							std::cout << "Client has closed the connection." << std::endl;
							
							std::for_each(ready_writers.begin(), ready_writers.end(), [&](Socket *client){
								client->send("User has quit the server.\n");
							});
						}
						selector.remove(current);
						Socket::release(&current);
					} else {
						// Send received message to all users
						std::for_each(ready_writers.begin(), ready_writers.end(), [&](Socket *client){
							client->send(buffer);
						});
					}
				}
			});
	}
	return EXIT_SUCCESS;
}
