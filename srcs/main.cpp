/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/03/24 23:07:41 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include "../include/Socket.hpp"
#include "../include/Network.hpp"

Socket *server = NULL;
Socket *new_sock;

void release_socket(Socket **sock){
    Socket *socket = *sock;

    if ( socket != NULL ){
        socket->close();
        delete socket;
        *sock = NULL;
    }
}

void sig_handler(__attribute__((unused)) int sig) {
    std::cout << "\nShutdown server\n";

    release_socket(&server);
    release_socket(&new_sock);
}

int main()
{
    std::pair<std::string, std::string>     host("", "3490");
    std::string                             buffer;

    signal(SIGINT, sig_handler);

    server = new Socket(AF_INET, SOCK_STREAM);
    try {
        server->bind(host.first, host.second);

        while ( true ) {
            try {
                server->listen(5);
                new_sock = server->accept();

                std::cout << "New connection from : " << new_sock->storage() << std::endl;

                while ( true ){
                    new_sock->recv(buffer);

                    if (!buffer.empty())
                        buffer.resize(buffer.size() - 1);

                    if (buffer == "ping"){
                        new_sock->send("pong\n");
                        std::cout << "PONG" << std::endl;
                        break;
                    } else {
                        new_sock->send("unknown command\n");
                    }
                }

                buffer.clear();
                release_socket(&new_sock);
            } catch (std::exception &e) { std::cout << e.what() << std::endl; break; }
        }
    } catch ( std::exception &e ){
        std::cout << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
