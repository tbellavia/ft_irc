//
// Created by kyoto on 13/04/2022.
//

# include "../include/network/Socket.hpp"

Socket::Socket(Socket const &sock, int fd, SocketStorage const &storage) :
	m_domain(sock.m_domain),
	m_type(sock.m_type),
	m_protocol(sock.m_protocol),
	m_blocking(sock.m_blocking),
	m_fd(fd),
	m_addr(sock.m_addr),
	m_storage(storage)
{
	m_addr.ai_family = storage.storage.ss_family;
	m_addr.ai_addr = (sockaddr*)&storage.storage;
}

Socket::Socket() : m_domain(), m_type(), m_protocol(), m_blocking(true), m_fd(net::FD_UNSET), m_addr(), m_storage() { }

Socket::Socket(int domain, int type, int protocol, bool blocking) :
	m_domain(domain),
	m_type(type),
	m_protocol(protocol),
	m_blocking(blocking),
	m_fd(net::FD_UNSET),
	m_addr(),
	m_storage()
{
	m_fd = socket(m_domain, m_type, m_protocol);
	if ( m_fd == -1 )
		throw SocketException("socket failed exception");
	if ( !blocking )
		::fcntl(m_fd, F_SETFL, O_NONBLOCK);
}

Socket::Socket(Socket const &other) :
	m_domain(other.m_domain),
	m_type(other.m_type),
	m_protocol(other.m_protocol),
	m_blocking(other.m_blocking),
	m_fd(other.m_fd),
	m_addr(other.m_addr),
	m_storage(other.m_storage) { }

Socket &Socket::operator=(Socket const &other) {
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

Socket::~Socket() {

}

/**
 * Access functions
 */

Socket::SocketStorage const &Socket::storage() const { return m_storage; }

/**
 * Get the underlying file descriptor
 */
int Socket::fd() const { return m_fd; }

std::string Socket::ip() const { return m_storage.get_ip(); }

void Socket::set_blocking(bool blocking) {
	int opts = ::fcntl(m_fd, F_GETFL);

	m_blocking = blocking;
	if ( blocking && m_fd != net::FD_UNSET ){
		::fcntl(m_fd, opts & (~O_NONBLOCK));
	}
	if ( !blocking && m_fd != net::FD_UNSET ){
		::fcntl(m_fd, O_NONBLOCK);
	}
}

/**
 * Socket interface
 */

void Socket::bind(std::string const &host, std::string const &port)  {
	const char  *node = (host.length() == 0) ? NULL : host.c_str();
	addrinfo    *infos;

	int status = net::tcp::getaddrinfo(node, port.c_str(), &infos);
	if ( status != 0 )
		throw SocketGaiException(status);
	m_addr = *infos;
	if ( ::bind(m_fd, m_addr.ai_addr, m_addr.ai_addrlen) == -1 )
		throw SocketException("bind exception");
}

void Socket::connect(std::string const &host, std::string const &port) {
	const char  *node = (host.length() == 0) ? NULL : host.c_str();
	addrinfo    *infos;

	int status = net::tcp::getaddrinfo(node, port.c_str(), &infos);
	if ( status != 0 )
		throw SocketGaiException(status);
	m_addr = *infos;
	if ( ::connect(m_fd, m_addr.ai_addr, m_addr.ai_addrlen) == -1 )
		throw SocketException("connect exception");
}

void Socket::listen(int n) const {
	if ( ::listen(m_fd, n) == -1 )
		throw SocketException("listen exception");
}

Socket *Socket::accept() const {
	SocketStorage   storage;

	int new_fd = ::accept(m_fd, (sockaddr*)&storage.storage, &storage.length);
	if ( new_fd == -1 )
		throw SocketException("accept exception");
	return new Socket(*this, new_fd, storage);
}

ssize_t Socket::send(const void *buf, int len, int flags) const {
	return ::send(m_fd, buf, len, flags);
}

ssize_t Socket::send(std::string const &msg, int flags) const {
	return ::send(m_fd, msg.c_str(), msg.length(), flags);
}

/**
 * Ideas for recv method
 *
 * - Write the received packet into a `stream` like `stringstream` ?
 */
ssize_t Socket::recv(void *buf, size_t len, int flags) const {
	return ::recv(m_fd, buf, len, flags);
}

/**
 * Recv wrapper.
 *
 * Recv wrapper that takes string buffer.
 */
ssize_t Socket::recv(std::string &s, int flags) const {
	ssize_t                 bytes = 0;
	char                    buf[BUF_SIZE];

	if ( (bytes = ::recv(m_fd, buf, BUF_SIZE, flags)) == -1 )
		return -1;
	s.append(buf, bytes);
	return bytes;
}

/**
 * Recv wrapper.
 *
 * Recv wrapper that will aggregate into @s until @seq is found.
 */
ssize_t Socket::recv(std::string &s, std::string const &seq, int flags) const {
	ssize_t                 bytes = 0;
	char                    buf[BUF_SIZE];

	while ( (bytes = ::recv(m_fd, buf, BUF_SIZE, flags)) > 0 ) {
		s.append(buf, bytes);

		if ( ft::ends_with(s, seq) )
			return bytes;
	}
	return bytes;
}

void Socket::close() const {
	::close(m_fd);
}

void Socket::shutdown(int how) const {
	if ( ::shutdown(m_fd, how) == -1 )
		throw SocketException();
}

int Socket::setsockopt(int level, int optname, const void *optval, socklen_t optlen) const {
	return ::setsockopt(m_fd, level, optname, optval, optlen);
}

int Socket::getsockopt(int level, int optname, void *optval, socklen_t *optlen) const {
	return ::getsockopt(m_fd, level, optname, optval, optlen);
}

void Socket::release(Socket **socket){
	if ( *socket != NULL ){
		(*socket)->close();
		delete *socket;
		*socket = NULL;
	}
}

Socket *Socket::create_tcp_socket() {
	return new Socket(AF_INET, SOCK_STREAM);
}


// Socket internals


void *get_in_addr(sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

Socket::SocketStorage::SocketStorage() : storage(), length(sizeof(sockaddr_storage)) { }

Socket::SocketStorage::SocketStorage(sockaddr_storage storage_, socklen_t length_)
	: storage(storage_), length(length_) { }

Socket::SocketStorage::SocketStorage(Socket::SocketStorage const &other)
	: storage(other.storage), length(other.length) { }

Socket::SocketStorage &Socket::SocketStorage::operator=(SocketStorage const &other) {
	if ( &other == this )
		return *this;
	storage = other.storage;
	length = other.length;
	return *this;
}

std::string
Socket::SocketStorage::get_ip() const {
	char addr[INET6_ADDRSTRLEN];

	const char *status = inet_ntop(storage.ss_family, get_in_addr((sockaddr*)&storage), addr, sizeof addr);

	if ( status == NULL )
		return "";
	return addr;
}

std::ostream &operator<<(std::ostream &os, Socket::SocketStorage const &s){
	os << s.get_ip();
	return os;
}

/**
 * A subclass of std::exception that represent a generic
 * exception that doesn't fit in `SocketGaiException` or
 * `SocketHostException`.
 */

Socket::SocketException::SocketException() : description("generic exception") { }
Socket::SocketException::SocketException(char const *desc) : std::exception(), description(desc) { }
char const *Socket::SocketException::what() const throw() {
	return description;
}

/**
 * A subclass of SocketException, this exception is raised for
 * address-related errors by `getaddrinfo` and `getnameinfo()`.
 */
Socket::SocketGaiException::SocketGaiException() : SocketException(), gai_error(0) { }
Socket::SocketGaiException::SocketGaiException(int error) : SocketException(), gai_error(error) { }
char const *Socket::SocketGaiException::what() const throw() {
	return "gai exception";
}

bool operator==(Socket const &a, Socket const &b){
	return a.fd() == b.fd();
}

bool operator!=(Socket const &a, Socket const &b){
	return !(a == b);
}
