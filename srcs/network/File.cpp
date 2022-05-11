/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:04:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/14 23:43:57 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"
#include <iostream>

File::File() : m_socket(NULL), m_events(0), m_buffer(), m_requests() { }

File::File(Socket *socket, int events) : 
	m_socket(socket),
	m_events(events),
	m_buffer(),
	m_requests() { }

File::File(File const &other) : 
	m_socket(other.m_socket), 
	m_events(other.m_events), 
	m_buffer(other.m_buffer),
	m_requests(other.m_requests) { }

File &File::operator=(File const &other) {
	if ( this == &other )
		return *this;
	m_socket = other.m_socket;
	m_events = other.m_events;
	m_buffer = other.m_buffer;
	m_requests = other.m_requests;
	return *this;
}

File::~File() {
	
}

Socket *File::socket() {
	return m_socket;
}

std::string const &File::buffer() const {
	return m_buffer;
}

bool File::isset(int event) const {
	return m_events & event;
}

/* Request Queue Interface */

/**
 * Push
 * 
 * Append the request into an internal buffer,
 * if the terminator is found, then the request
 * is flushed from the buffer and enqueued in
 * an internal request queue.
 */
void
File::push_request(std::string const &req){
	std::vector<std::string> parts;
	size_t pos;

	m_buffer.append(req);
	while ( (pos = m_buffer.find(CRLF)) != std::string::npos ){
		parts = ft::split_one(m_buffer, CRLF);

		if ( parts.size() == 1 ) {
			m_buffer = parts[0];
		} else {
			m_requests.push( parts[0] );
			m_buffer = parts[1];
		}
	}
}

/**
 * Pop
 * 
 * Pop a request from the internal request queue.
 * If there are no requests available, calling
 * pop result in an undefined behaviour.
 * 
 * You should ALWAYS call available to check
 * whether there are requests to retrieve.
 */
std::string
File::pop_request() {
	std::string front = m_requests.front();

	m_requests.pop();
	return front;
}

/**
 * Available
 * 
 * Returns True if there are available
 * requests into the requests queue, otherwise
 * False.
 */
bool
File::available_request() const {
	return !m_requests.empty();
}

void
File::clear() {
	m_buffer.clear();
 }

void
File::push_response(std::string const &response){
	m_responses.push(response);
}

std::pair<bool, std::string>
File::pop_response() {
	std::string ret;
	std::string curr = m_responses.front();
	bool available = true;

	if ( curr.size() > BUF_SIZE) {
		ret = curr.substr(0, BUF_SIZE);
		m_responses.front() = curr.substr(BUF_SIZE, curr.size());
	} else {
		ret = curr;
		m_responses.pop();
		available = false;
	}
	return std::make_pair(available, ret);
}

bool
File::available_response() const {
	return !m_responses.empty();
}