//
// Created by kyoto on 17/03/2022.
//

#ifndef FT_IRC_SOCKET_HPP
# define FT_IRC_SOCKET_HPP


# include <cstring>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

// TODO: Remove this includes
# include <iostream>

# define FD_UNSET -1

class Socket {
    struct addrinfo        *m_addr;
    int                     m_fd;
    bool                    m_blocking;
public:
    Socket(struct addrinfo *addr, int fd = FD_UNSET, int blocking = true)
        : m_addr(addr), m_fd(fd), m_blocking(blocking) {
        (void)m_blocking;
        if ( m_fd == -1 )
            m_fd = socket(m_addr->ai_family, m_addr->ai_socktype, m_addr->ai_protocol);
        std::cout << "FD : " << m_fd << std::endl;
    }

    // TODO: Manage exception on bind failure
    void sock_bind(const struct addrinfo *addr = NULL ) const {
        const struct addrinfo *addr_ = (addr) ? addr : m_addr;

        bind(m_fd, addr_->ai_addr, addr_->ai_addrlen);
    }

    // TODO: Manage exception on connect failure
    void sock_connect(const struct addrinfo *addr = NULL) const {
        const struct addrinfo *addr_ = (addr) ? addr : m_addr;

        connect(m_fd, addr_->ai_addr, addr_->ai_addrlen);
    }
};

#endif //FT_IRC_SOCKET_HPP
