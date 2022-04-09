/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/06 18:31:24 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tony on 05/04/2022.
//

#ifndef FT_IRC_SELECTOR_HPP
#define FT_IRC_SELECTOR_HPP

# include <sys/select.h>
# include <vector>
# include <map>
# include "Socket.hpp"
# include "Network.hpp"

# define CRLF "\r\n"

class Selector {
public:
	enum {
		READ = 0x01,
		WRITE = 0x01 << 1,
		EXCEPT = 0x01 << 2,
	};

	class SelectorValue {
		Socket          *m_socket;
		int             m_events;
        std::string     m_buffer;
	public:
		SelectorValue() : m_socket(NULL), m_events(0), m_buffer() { }
		SelectorValue(Socket *socket, int events) : m_socket(socket), m_events(events), m_buffer() { }
		SelectorValue(SelectorValue const &other) : m_socket(other.m_socket), m_events(other.m_events), m_buffer(other.m_buffer) {}
		SelectorValue &operator=(SelectorValue const &other) {
			if ( this == &other )
				return *this;
			m_socket = other.m_socket;
			m_events = other.m_events;
            m_buffer = other.m_buffer;
			return *this;
		}

		Socket *socket() {
			return m_socket;
		}

        std::string const &buffer() const {
            return m_buffer;
        }

		bool is_event_set(int event) const {
			return m_events & event;
		}

        void append(std::string const &s){
            m_buffer.append(s);
        }

        /**
         * Full
         *
         * Returns a pair of bool and string, if the boolean is True, it means
         * that the packet is complete and the string contains the content of
         * the packet.
         * If false, it means that the packet is not complete and it lacks of contents.
         */
         bool has_terminator(std::string const terminator = CRLF) const{
            return m_buffer.find(terminator) != std::string::npos;
         }

         bool full() const {
             return m_buffer.find(CRLF) == std::string::npos;
         }

        std::string flush() {
            std::vector<std::string> strings = ft::split(m_buffer, CRLF);

            if ( strings.size() > 1 ){
                m_buffer = strings[1];
            }
            return strings[0];
        }

        void clear() {
             m_buffer.clear();
         }
	};
    typedef std::vector<SelectorValue*>             ready_type;
	typedef std::map<int, SelectorValue*>           entries_type;
	typedef entries_type::value_type               entries_value_type;
	typedef entries_type::iterator                 entries_iterator;
	typedef entries_type::const_iterator           entries_const_iterator;
private:
	fd_set                          m_read;
	fd_set                          m_write;
	std::map<int, SelectorValue*>    m_entries;
	int                             m_max_fd;
public:
	Selector() : m_read(), m_write(), m_entries(), m_max_fd(net::FD_UNSET) {
		FD_ZERO(&m_read);
		FD_ZERO(&m_write);
	}

	Selector(Selector const &other)
		: m_read(other.m_read), m_write(other.m_write), m_entries(other.m_entries), m_max_fd(other.m_max_fd) { }

	Selector &operator=(Selector const &other) {
		if ( this == &other )
			return *this;
		m_read = other.m_read;
		m_write = other.m_write;
		m_entries = other.m_entries;
		m_max_fd = other.m_max_fd;
		return *this;
	}

    ~Selector() {
        std::map<int, SelectorValue*>::iterator it = m_entries.begin();

        for ( ; it != m_entries.end() ; ++it ){
            delete (*it).second;
        }
    }

	/* Getters / Setters */
	entries_type const &get_entries() const {
		return m_entries;
	}

	/* Iterators forwarding */

	entries_iterator begin() { return m_entries.begin(); }
	entries_const_iterator begin() const { return m_entries.begin(); }

	entries_iterator end() { return m_entries.end(); }
	entries_const_iterator end() const { return m_entries.end(); }

	/* Interface */
	void add(Socket *socket, int events) {
		if ( socket != NULL ){
			SelectorValue *val = new SelectorValue(socket, events);
			int fd = socket->fd();

			if ( val->is_event_set(READ) )
				FD_SET(fd, &m_read);
			if ( val->is_event_set(WRITE) )
				FD_SET(fd, &m_write);
			m_max_fd = std::max(m_max_fd, fd);
			m_entries.insert(std::make_pair(fd, val));
		}
	}

    void remove(SelectorValue *value){
        if ( value != NULL )
            this->remove(value->socket());
    }

	void remove(Socket *socket) {
		if ( socket != NULL ){
			SelectorValue       *value;
			entries_iterator    found = m_entries.find(socket->fd());

			if ( found == m_entries.end() )
				return ;
			value = found->second;
			if ( value->is_event_set(READ) )
				FD_CLR(socket->fd(), &m_read);
			if ( value->is_event_set(WRITE) )
				FD_CLR(socket->fd(), &m_write);
			m_entries.erase(found);
            delete value;
		}
	}

	std::pair<ready_type, ready_type> select(int seconds = -1, int useconds = -1){
		ready_type  ready_readers;
		ready_type  ready_writers;
		timeval     timeout = (timeval){ seconds, (useconds == -1) ? 0 : useconds };
		fd_set      read_set = m_read;
		fd_set      write_set = m_write;

		if ( seconds == -1 )
			::select(m_max_fd + 1, &read_set, &write_set, NULL, NULL);
		else
			::select(m_max_fd + 1, &read_set, &write_set, NULL, &timeout );

		for ( std::map<int, SelectorValue*>::iterator it = m_entries.begin() ; it != m_entries.end() ; ++it ){
			Socket  *socket = it->second->socket();
			int     fd = socket->fd();

			if ( it->second->is_event_set(READ) && FD_ISSET(fd, &read_set) )
				ready_readers.push_back( it->second );
			if ( it->second->is_event_set(WRITE) && FD_ISSET(fd, &write_set) )
				ready_writers.push_back( it->second );
		}
		return std::make_pair( ready_readers, ready_writers );
	}
};

#endif //FT_IRC_SELECTOR_HPP
