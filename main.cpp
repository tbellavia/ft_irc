/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/09 11:36:14 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <exception>
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
