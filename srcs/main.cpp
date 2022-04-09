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
#include "../include/IRCServer.hpp"

int main(int argc, char *argv[])
{
	if ( argc != 3 ){
		std::cerr << "usage: server host port" << std::endl;
		return EXIT_FAILURE;
	}
    IRCServer server(argv[1], argv[2], true);

    server.serve_forever();
	return EXIT_SUCCESS;
}
