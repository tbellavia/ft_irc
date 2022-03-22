//
// Created by kyoto on 17/03/2022.
//

#ifndef FT_IRC_SOCKET_HPP
# define FT_IRC_SOCKET_HPP


# include <cstring>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <stdexcept>

#include "Network.hpp"


// TODO: Remove this includes
# include <cstdio>

# define FD_UNSET -1

void *get_in_addr(sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

class Socket {
public:
    /* Internal implementation */
    struct SocketStorage {
        sockaddr_storage    storage;
        socklen_t           length;

        SocketStorage() : storage(), length(sizeof(sockaddr_storage)) { }
        SocketStorage(sockaddr_storage const &storage_, socklen_t length_) : storage(storage_), length(length_) { }
        SocketStorage(SocketStorage const &other) : storage(other.storage), length(other.length) { }
        SocketStorage &operator=(SocketStorage const &other) {
            if ( &other == this )
                return *this;
            storage = other.storage;
            length = other.length;
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, SocketStorage const &s){
            char addr[INET6_ADDRSTRLEN];

            inet_ntop(s.storage.ss_family, get_in_addr((sockaddr*)&s.storage), addr, sizeof addr);
            os << addr;
            return os;
        }
    };

    /**
     * A subclass of std::exception that represent a generic
     * exception that doesn't fit in `SocketGaiException` or
     * `SocketHostException`.
     */
    struct SocketException : public std::exception {
        char const *description;

        SocketException() : description("generic exception") { }
        explicit SocketException(char const *desc) : std::exception(), description(desc) { }

        virtual char const *what() const throw() {
            return description;
        }
    };

    /**
     * A subclass of SocketException, this exception is raised for
     * address-related errors by `getaddrinfo` and `getnameinfo()`.
     */
    struct SocketGaiException : public SocketException {
        int     gai_error;

        SocketGaiException() : SocketException(), gai_error(0) { }
        explicit SocketGaiException(int error) : SocketException(), gai_error(error) { }

        virtual char const *what() const throw() {
            return "gai exception";
        }
    };

    /**
     * A subclass of SocketException, this exception is raised for
     * address-related errors and for functions thar use h_errno,
     * including `gethostbyname_ex()` and `gethostbyaddr()`.
     */
    struct SocketHostException : public SocketException {
        int h_error;

        SocketHostException() : SocketException(), h_error(0) { }
        explicit SocketHostException(int error) : SocketException(), h_error(error) { }

        virtual char const *what() const throw() {
            return "host exception";
        }
    };
private:
    int                 m_domain;
    int                 m_type;
    int                 m_protocol;
    bool                m_blocking;
    int                 m_fd;
    addrinfo            *m_addr;
    SocketStorage       m_storage;
public:
    Socket() : m_domain(), m_type(), m_protocol(), m_blocking(true), m_fd(FD_UNSET), m_addr(NULL), m_storage() { }

    explicit Socket(int domain, int type, int protocol, bool blocking = true) :
        m_domain(domain),
        m_type(type),
        m_protocol(protocol),
        m_blocking(blocking),
        m_fd(FD_UNSET),
        m_addr(NULL),
        m_storage()
    {
        m_fd = socket(m_domain, m_type, m_protocol);
        if ( m_fd == -1 )
            throw SocketException();
    }

    Socket(Socket const &other) :
        m_domain(other.m_domain),
        m_type(other.m_type),
        m_protocol(other.m_protocol),
        m_blocking(other.m_blocking),
        m_fd(other.m_fd),
        m_addr(other.m_addr),
        m_storage(other.m_storage) { }

    Socket &operator=(Socket const &other) {
        if ( &other == this )
            return *this;
        m_domain = other.m_domain;
        m_type = other.m_type;
        m_protocol = other.m_protocol;
        m_blocking = other.m_blocking;
        m_fd = other.m_fd;
        m_addr = other.m_addr;
        m_storage = other.m_storage;
        return *this;
    }

    // TODO: Manage exception on bind failure
    void sock_bind(std::string const &host, std::string const &port)  {
        const char  *node = (host.length() == 0) ? NULL : host.c_str();

        int status = network::tcp::getaddrinfo(node, port.c_str(), &m_addr);
        if ( status != 0 )
            throw SocketGaiException(status);
        if ( bind(m_fd, m_addr->ai_addr, m_addr->ai_addrlen) == -1 )
            throw SocketException();
    }

    // TODO: Manage exception on connect failure
    void sock_connect(std::string const &host, std::string const &port) {
        const char  *node = (host.length() == 0) ? NULL : host.c_str();

        int status = network::tcp::getaddrinfo(node, port.c_str(), &m_addr);
        if ( status != 0 )
            throw SocketGaiException(status);
        if ( connect(m_fd, m_addr->ai_addr, m_addr->ai_addrlen) == -1 )
            throw SocketException();
    }

    // TODO: Manage exception on listen failure
    void sock_listen(int n) const {
        listen(m_fd, n);
    }

    // TODO: Manage exception on accept failure
    Socket sock_accept() const {
        SocketStorage storage;

        int new_fd = accept(m_fd, (sockaddr*)&storage.storage, &storage.length);
        if ( new_fd == -1 )
            throw std::exception();
        return Socket(m_addr, new_fd, storage, m_blocking);
    }

    void sock_send(const void *buf, int len, int flags) const {
        send(m_fd, buf, len, flags);
    }

    void sock_send(std::string const &msg, int flags = 0) const {
        send(m_fd, msg.c_str(), msg.length(), flags);
    }

    /**
     * Ideas for recv method
     *
     * - Write the received packet into a `stream` like `stringstream` ?
     */
//    int sock_recv() const{
//
//    }

    void sock_close() const {
        close(m_fd);
    }
};

#endif //FT_IRC_SOCKET_HPP
