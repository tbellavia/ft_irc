/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 22:47:55 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by kyoto on 17/03/2022.
//

#ifndef FT_IRC_NETWORK_HPP
#define FT_IRC_NETWORK_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstddef>
#include <cstring>
#include <string>

namespace net {
	const int FD_UNSET = -1;
	const std::string CRLF = "\r\n";

	std::string ston(std::string const &s, std::string const &terminator = CRLF);

	namespace tcp {
		int			getaddrinfo(const char *node, const char *service, struct addrinfo **res);
		addrinfo	*getaddrinfo(const char *node, const char *service);
	}

	namespace udp {
		int			getaddrinfo(const char *node, const char *service, struct addrinfo **res);
		addrinfo	*getaddrinfo(const char *node, const char *service);
	}
}

#endif //FT_IRC_NETWORK_HPP
