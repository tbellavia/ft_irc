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

namespace network {
    namespace tcp {
        int getaddrinfo(const char *node, const char *service, struct addrinfo **res) {
            struct addrinfo hints;

            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_flags = AI_PASSIVE;
            return ::getaddrinfo(node, service, &hints, res);
        }

        // TODO: Properly manage errors on call to getaddrinfo
        struct addrinfo *getaddrinfo(const char *node, const char *service){
            struct addrinfo *res;

            if ( getaddrinfo(node, service, &res) != 0 )
                return NULL;
            return res;
        }
    }

    namespace udp {
        int getaddrinfo(const char *node, const char *service, struct addrinfo **res) {
            struct addrinfo hints;

            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_DGRAM;
            hints.ai_flags = AI_PASSIVE;
            return ::getaddrinfo(node, service, &hints, res);
        }

        struct addrinfo *getaddrinfo(const char *node, const char *service){
            struct addrinfo *res;

            if ( getaddrinfo(node, service, &res) != 0 )
                return NULL;
            return res;
        }
    }
}

#endif //FT_IRC_NETWORK_HPP
