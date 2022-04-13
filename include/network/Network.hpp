/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/06 18:31:07 by bbellavi         ###   ########.fr       */
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

namespace net {
    const int FD_UNSET = -1;

    namespace tcp {
        int         getaddrinfo(const char *node, const char *service, struct addrinfo **res);
        addrinfo    *getaddrinfo(const char *node, const char *service);
    }

    namespace udp {
        int         getaddrinfo(const char *node, const char *service, struct addrinfo **res);
        addrinfo    *getaddrinfo(const char *node, const char *service);
    }
}

#endif //FT_IRC_NETWORK_HPP
