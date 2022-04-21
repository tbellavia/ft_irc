/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:04:58 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 22:47:45 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by kyoto on 13/04/2022.
//

# include "Network.hpp"


/**
 * ston
 * 
 * Takes a string @s and add a network terminator.
 * Default is CR LF.
 */
std::string net::ston(std::string const &s, std::string const &terminator) {
	return s + terminator;
}

int net::tcp::getaddrinfo(const char *node, const char *service, struct addrinfo **res) {
	addrinfo hints;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	return ::getaddrinfo(node, service, &hints, res);
}

addrinfo *net::tcp::getaddrinfo(const char *node, const char *service){
	addrinfo *res;

	if ( getaddrinfo(node, service, &res) != 0 )
		return NULL;
	return res;
}

int net::udp::getaddrinfo(const char *node, const char *service, addrinfo **res) {
	addrinfo hints;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	return ::getaddrinfo(node, service, &hints, res);
}

addrinfo *net::udp::getaddrinfo(const char *node, const char *service){
	addrinfo *res;

	if ( getaddrinfo(node, service, &res) != 0 )
		return NULL;
	return res;
}