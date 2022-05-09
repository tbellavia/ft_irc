/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:32 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/26 01:00:25 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>

# include <stdexcept>
# include <algorithm>

# include "Network.hpp"
# include "../Utils.hpp"


// TODO: Remove this includes
# include <cstdio>

# define BUF_SIZE 512

void *get_in_addr(sockaddr *sa);

class Socket {
public:
	/* Internal implementation */
	struct SocketStorage {
		sockaddr_storage    storage;
		socklen_t           length;

		SocketStorage();
		SocketStorage(sockaddr_storage storage_, socklen_t length_);
		SocketStorage(SocketStorage const &other);
		SocketStorage &operator=(SocketStorage const &other);
		
		std::string get_ip() const;
		
		friend std::ostream &operator<<(std::ostream &os, SocketStorage const &s);
	};

	/**
	 * A subclass of std::exception that represent a generic
	 * exception that doesn't fit in `SocketGaiException` or
	 * `SocketHostException`.
	 */
	struct SocketException : public std::exception {
		char const *description;

		SocketException();
		explicit SocketException(char const *desc);
		virtual char const *what() const throw();
	};

	/**
	 * A subclass of SocketException, this exception is raised for
	 * address-related errors by `getaddrinfo` and `getnameinfo()`.
	 */
	struct SocketGaiException : public SocketException {
		int     gai_error;

		SocketGaiException();
		explicit SocketGaiException(int error);
		virtual char const *what() const throw();
	};
private:
	int                 m_domain;
	int                 m_type;
	int                 m_protocol;
	bool                m_blocking;
	int                 m_fd;
	addrinfo            m_addr;
	SocketStorage       m_storage;

	Socket(Socket const &sock, int fd, SocketStorage const &storage);
public:
	Socket();
	explicit Socket(int domain, int type, int protocol = 0, bool blocking = true);
	Socket(Socket const &other);
	Socket &operator=(Socket const &other);
	~Socket();


	int						fd() const;
	std::string				ip() const;
	void					set_blocking(bool blocking);
	SocketStorage const		&storage() const;

	void					bind(std::string const &host, std::string const &port);
	void					connect(std::string const &host, std::string const &port);
	void					listen(int n) const;
	Socket					*accept() const;
	ssize_t					send(const void *buf, int len, int flags) const;
	ssize_t					send(std::string const &msg, int flags = 0) const;
	ssize_t					recv(void *buf, size_t len, int flags = 0) const;
	ssize_t					recv(std::string &s, int flags = 0) const;
	ssize_t					recv(std::string &s, std::string const &seq, int flags = 0) const;
	void					close() const;
	void					shutdown(int how) const;
	int						setsockopt(int level, int optname, const void *optval, socklen_t optlen) const;
	int						getsockopt(int level, int optname, void *optval, socklen_t *optlen) const;

	static void				release(Socket **socket);
	static Socket			*create_tcp_socket();
};

bool operator==(Socket const &a, Socket const &b);
bool operator!=(Socket const &a, Socket const &b);

#endif //FT_IRC_SOCKET_HPP
