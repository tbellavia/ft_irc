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
#include "../include/Socket.hpp"
#include "../include/Network.hpp"

int main()
{
    const char *addr = NULL;
    const char *proto = "3490";

    struct addrinfo *res = network::tcp::getaddrinfo(addr, proto);

//    std::cout << "Create socket to addr " << addr << ":" << proto << std::endl;

    Socket sock(res);

    sock.sock_bind();
    return EXIT_SUCCESS;
}
