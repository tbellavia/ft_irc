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



// TODO: Remove this includes
# include <cstdio>

# define FD_UNSET -1

void *get_in_addr(sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Forward definition
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

class Socket {
    addrinfo            m_addr;
    int                 m_fd;
    SocketStorage       m_storage;
    bool                m_blocking;
public:
    explicit Socket(addrinfo addr, int fd = FD_UNSET, SocketStorage const &storage = SocketStorage(), bool blocking = true )
        : m_addr(addr), m_fd(fd), m_storage(storage), m_blocking(blocking) {
        (void)m_blocking;
        if ( m_fd == -1 )
            m_fd = socket(m_addr.ai_family, m_addr.ai_socktype, m_addr.ai_protocol);
        printf("Socket<fd=%i>\n", m_fd);
    }

    Socket(Socket const &other)
        : m_addr(other.m_addr), m_fd(other.m_fd), m_storage(other.m_storage), m_blocking(other.m_blocking) { }

    Socket &operator=(Socket const &other) {
        if ( &other == this )
            return *this;
        m_addr = other.m_addr;
        m_fd = other.m_fd;
        m_storage = other.m_storage;
        m_blocking = other.m_blocking;
        return *this;
    }

    addrinfo const &get_addrinfo() const {
        return m_addr;
    }

    int get_fd() const {
        return m_fd;
    }

    SocketStorage const &get_storage() const {
        return m_storage;
    };

    bool is_blocking() const {
        return m_blocking;
    }

    // TODO: Manage exception on bind failure
    void sock_bind() const {
        bind(m_fd, m_addr.ai_addr, m_addr.ai_addrlen);
    }

    // TODO: Manage exception on connect failure
    void sock_connect() const {
        connect(m_fd, m_addr.ai_addr, m_addr.ai_addrlen);
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
