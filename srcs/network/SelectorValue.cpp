/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SelectorValue.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:04:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:14:47 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SelectorValue.hpp"

SelectorValue::SelectorValue() : m_socket(NULL), m_events(0), m_buffer() { }
SelectorValue::SelectorValue(Socket *socket, int events) : m_socket(socket), m_events(events), m_buffer() { }
SelectorValue::SelectorValue(SelectorValue const &other) : m_socket(other.m_socket), m_events(other.m_events), m_buffer(other.m_buffer) {}

SelectorValue &SelectorValue::operator=(SelectorValue const &other) {
	if ( this == &other )
		return *this;
	m_socket = other.m_socket;
	m_events = other.m_events;
	m_buffer = other.m_buffer;
	return *this;
}

SelectorValue::~SelectorValue() {
	
}

Socket *SelectorValue::socket() {
	return m_socket;
}

std::string const &SelectorValue::buffer() const {
	return m_buffer;
}

bool SelectorValue::is_event_set(int event) const {
	return m_events & event;
}

void SelectorValue::append(std::string const &s){
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
bool
SelectorValue::has_terminator(std::string const &terminator) const {
	return m_buffer.find(terminator) != std::string::npos;
}

bool
SelectorValue::full() const {
	 return m_buffer.find(CRLF) == std::string::npos;
}

std::string 
SelectorValue::flush() {
	std::vector<std::string> strings = ft::split(m_buffer, CRLF);

	if ( strings.size() > 1 ){
		m_buffer = strings[1];
	}
	return strings[0];
}

void
SelectorValue::clear() {
	 m_buffer.clear();
 }