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

void
File::set_event(int event) {
	m_events |= event;
}

void
File::unset_event(int event) {
	m_events &= ~event;
}

Socket*
File::socket() {
	return m_socket;
}

std::string const&
File::buffer() const {
	return m_buffer;
}

bool
File::isset_event(int event) const {
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

std::string
File::pop_response() {
	return m_responses.pop();
}

bool
File::available_response() const {
	return m_responses.available();
}

void
File::seek_response(size_t offset) {
	m_responses.seek(offset);
}

/* Response buffer */

File::ResponseBuffer::ResponseBuffer() : 
	m_responses(), 
	m_begin() { }

File::ResponseBuffer::ResponseBuffer(ResponseBuffer const &other) :
	m_responses(other.m_responses),
	m_begin(other.m_begin) { }

File::ResponseBuffer&
File::ResponseBuffer::operator=(ResponseBuffer const &other) {
	if ( &other == this )
		return *this;
	m_responses = other.m_responses;
	m_begin = other.m_begin;
	return *this;
}

File::ResponseBuffer::~ResponseBuffer() { }

std::string
File::ResponseBuffer::pop() {
	m_responses = m_responses.substr(m_begin, m_responses.length());
	return m_responses;
}

void
File::ResponseBuffer::push(std::string const &response) {
	m_responses.append(response);
}

void
File::ResponseBuffer::seek(size_t offset) {
	m_begin = offset;
}

bool
File::ResponseBuffer::available() const {
	return !m_responses.empty();
}