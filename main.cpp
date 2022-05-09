/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/09 09:10:24 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <exception>
#include "App.hpp"

int main(int argc, char *argv[])
{
	if ( argc != 3 ){
		std::cerr << "usage: server host port" << std::endl;
		return EXIT_FAILURE;
	}
	std::string port = argv[1];
	std::string pass = argv[2];
	App app;

	try {
		app.start(port, pass);
	} catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
