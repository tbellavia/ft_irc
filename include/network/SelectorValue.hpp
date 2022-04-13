/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SelectorValue.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:53:04 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 00:58:24 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISELECTORVALUE_HPP
#define ISELECTORVALUE_HPP

# include <string>
# include "Socket.hpp"

# define CRLF "\r\n"

class SelectorValue {
	Socket			*m_socket;
	int				m_events;
	std::string		m_buffer;
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

#endif
