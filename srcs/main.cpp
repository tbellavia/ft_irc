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
#include "../include/Socket.hpp"
#include "../include/Network.hpp"

int main()
{
    const char *addr = "127.0.0.1";
    const char *proto = "3490";

    std::cout << "Listening " << addr << ":" << proto << std::endl;
    addrinfo *res = network::tcp::getaddrinfo(addr, proto);
    Socket server(*res);

    server.sock_bind();
    server.sock_listen(5);
    while ( true ){
        try {
            Socket client = server.sock_accept();

            std::cout << "Got connection from : " << client.get_storage() << std::endl;
            client.sock_send("Pong\n");
            client.sock_close();
        } catch ( std::exception &e ){
            std::cout << e.what() << std::endl;
        }
    }
    server.sock_close();
    return EXIT_SUCCESS;
}
