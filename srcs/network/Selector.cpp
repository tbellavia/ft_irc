//
// Created by kyoto on 13/04/2022.
//

#include "../include/network/Selector.hpp"

Selector::Selector() : m_read(), m_write(), m_entries(), m_max_fd(net::FD_UNSET) {
	FD_ZERO(&m_read);
	FD_ZERO(&m_write);
}

Selector::Selector(Selector const &other)
	: m_read(other.m_read), m_write(other.m_write), m_entries(other.m_entries), m_max_fd(other.m_max_fd) { }

Selector &Selector::operator=(Selector const &other) {
	if ( this == &other )
		return *this;
	m_read = other.m_read;
	m_write = other.m_write;
	m_entries = other.m_entries;
	m_max_fd = other.m_max_fd;
	return *this;
}

Selector::~Selector() {
	std::map<int, File*>::iterator it = m_entries.begin();

	for ( ; it != m_entries.end() ; ++it ){
		delete (*it).second;
	}
}

/* Getters / Setters */
std::map<int, File*> const&
Selector::get_entries() const {
	return m_entries;
}

void
Selector::add(Socket *socket, int events) {
	if ( socket != NULL ){
		File *val = new File(socket, events);
		int fd = socket->fd();

		if ( val->isset(READ) )
			FD_SET(fd, &m_read);
		if ( val->isset(WRITE) )
			FD_SET(fd, &m_write);
		m_max_fd = std::max(m_max_fd, fd);
		m_entries.insert(std::make_pair(fd, val));
	}
}

void
Selector::remove(Socket *socket) {
	if ( socket != NULL ){
		File								*value;
		std::map<int, File*>::iterator		found = m_entries.find(socket->fd());

		if ( found == m_entries.end() )
			return ;
		value = found->second;
		if ( value->isset(READ) )
			FD_CLR(socket->fd(), &m_read);
		if ( value->isset(WRITE) )
			FD_CLR(socket->fd(), &m_write);
		m_entries.erase(found);
		delete value;
	}
}

std::pair<std::set<File*>, std::set<File*> >
Selector::select(int seconds, int useconds){
	std::set<File*>  ready_readers;
	std::set<File*>  ready_writers;
	timeval     timeout = (timeval){ seconds, (useconds == -1) ? 0 : useconds };
	fd_set      read_set = m_read;
	fd_set      write_set = m_write;

	if ( seconds == -1 )
		::select(m_max_fd + 1, &read_set, &write_set, NULL, NULL);
	else
		::select(m_max_fd + 1, &read_set, &write_set, NULL, &timeout );

	for (std::map<int, File*>::iterator it = m_entries.begin() ; it != m_entries.end() ; ++it ){
		Socket  *socket = it->second->socket();
		int     fd = socket->fd();

		if ( it->second->isset(READ) && FD_ISSET(fd, &read_set) )
			ready_readers.insert( it->second );
		if ( it->second->isset(WRITE) && FD_ISSET(fd, &write_set) )
			ready_writers.insert( it->second );
	}
	return std::make_pair( ready_readers, ready_writers );
}

File*
Selector::find(Socket *socket){
	std::map<int, File*>::iterator found;

	if ( socket == NULL )
		return NULL;
	found = m_entries.find(socket->fd());
	if ( found == m_entries.end() )
		return NULL;
	return found->second;
}