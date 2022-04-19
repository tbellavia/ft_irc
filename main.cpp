/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/04/19 13:52:20 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
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

	app.start(port, pass);
	return EXIT_SUCCESS;
}
