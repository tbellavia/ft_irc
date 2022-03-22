/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/01/10 09:15:42 by lperson-         ###   ########.fr       */
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

void sig_handler(int sig) {
    (void)sig;
    std::cout << "\nShutdown server\n";
    server->close();
    delete server;

    if ( new_sock != NULL ){
        new_sock->close();
        delete new_sock;
    }
}

int main()
{
    signal(SIGINT, sig_handler);
    std::string     buffer;
    std::pair<std::string, std::string> host("", "3490");


    server = new Socket(AF_INET, SOCK_STREAM);
    server->bind("", "3490");
    while ( true ){
        try {
            server->listen(5);

            new_sock = server->accept();

            std::cout << "New connection from : " << new_sock->storage() << std::endl;

            new_sock->recv(buffer);
            printf("Received: |%s| %i\n", buffer.c_str(), (int)buffer.size());

            new_sock->send("pong\n");
            buffer.clear();

            new_sock->close();

            delete new_sock;
            new_sock = NULL;
        } catch ( std::exception &e ){
            break;
        }
    }
    return EXIT_SUCCESS;
}
