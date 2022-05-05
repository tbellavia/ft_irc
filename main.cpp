/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/04/26 01:12:52 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
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
		"127.0.0.1", 
		"ft.irc.com", 
		port, 
		"ft_oper", 
		"ft_oper", 
		10
	);

	app.start(config);
	return EXIT_SUCCESS;
}
