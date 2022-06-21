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
Selector::set(IFileObj *fileobj, int events) {
	if ( fileobj == NULL )
		return ;
	File *value = this->find(fileobj);
	int fd = fileobj->fd();

	if ( value == NULL )
		return ;

	value->set_event(events);
	if ( value->isset_event(READ) )
		FD_SET(fd, &m_read);
	if ( value->isset_event(WRITE) )
		FD_SET(fd, &m_write);
}

void
Selector::unset(IFileObj *fileobj, int events) {
	if ( fileobj == NULL )
		return;
	File *value = this->find(fileobj);
	int fd = fileobj->fd();

	if ( value == NULL )
		return;

	value->unset_event(events);
	if ( !value->isset_event(READ) )
		FD_CLR(fd, &m_read);
	if ( !value->isset_event(WRITE) )
		FD_CLR(fd, &m_write);
}

void
Selector::add(IFileObj *fileobj, int events) {
	if ( fileobj != NULL ){
		File *val = new File(fileobj, events);
		int fd = fileobj->fd();

		if ( val->isset_event(READ) )
			FD_SET(fd, &m_read);
		if ( val->isset_event(WRITE) )
			FD_SET(fd, &m_write);
		m_max_fd = std::max(m_max_fd, fd);
		m_entries.insert(std::make_pair(fd, val));
	}
}

void
Selector::remove(IFileObj *fileobj) {
	if ( fileobj != NULL ){
		File							*value;
		std::map<int, File*>::iterator	found = m_entries.find(fileobj->fd());

		if ( found == m_entries.end() )
			return ;
		value = found->second;
		if ( value->isset_event(READ) )
			FD_CLR(fileobj->fd(), &m_read);
		if ( value->isset_event(WRITE) )
			FD_CLR(fileobj->fd(), &m_write);
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
		IFileObj  *fileobj = it->second->fileobj();
		int     fd = fileobj->fd();

		if ( it->second->isset_event(READ) && FD_ISSET(fd, &read_set) )
			ready_readers.insert( it->second );
		if ( it->second->isset_event(WRITE) && FD_ISSET(fd, &write_set) )
			ready_writers.insert( it->second );
	}
	return std::make_pair( ready_readers, ready_writers );
}

File*
Selector::find(IFileObj *fileobj){
	std::map<int, File*>::iterator found;

	if ( fileobj == NULL )
		return NULL;
	found = m_entries.find(fileobj->fd());
	if ( found == m_entries.end() )
		return NULL;
	return found->second;
}