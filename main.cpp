/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/20 13:14:25 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <exception>
#include <iostream>
#include "App.hpp"

int main(int argc, char *argv[])
{
	if ( argc != 3 ){
		std::cerr << "usage: server port password" << std::endl;
		return EXIT_FAILURE;
	}
	App app;

	std::string port = argv[1];
	std::string pass = argv[2];

	IRC::ConfigServer config(
		pass, 
		"0.0.0.0",
		"ft.irc.com", 
		port, 
		"1.0",
		"ft_oper", 
		"ft_oper", 
		10
	);

	try {
		app.start(config);
	} catch (std::exception const &e) {
		std::cerr << "ft_irc: failed to start server: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
