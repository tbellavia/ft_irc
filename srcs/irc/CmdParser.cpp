/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 02:13:43 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/30 00:27:12 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdParser.hpp"


IRC::CmdParser::CmdParser(std::string const &request) : 
	m_request(request),
	m_start(0),
	m_current(0) { }

IRC::CmdParser::CmdParser(CmdParser const &other) :
	m_request(other.m_request),
	m_start(other.m_start),
	m_current(other.m_current) { }

IRC::CmdParser&
IRC::CmdParser::operator=(CmdParser const &other){
	if ( &other == this )
		return *this;
	m_request = other.m_request;
	m_start = other.m_start;
	m_current = other.m_current;
	return *this;
}

IRC::CmdParser::~CmdParser() { }

std::vector<std::string>
IRC::CmdParser::parse() {
	std::vector<std::string> tokens;

	if ( is_at_end() )
		return tokens;
	if ( peek() == ':' )
		tokens.push_back(parse_single_token());
	while ( !is_at_end() ){
		if ( isspace(peek()) ){
			if ( skip_space() )
				return tokens;
		}
		else if ( peek() == ':' ){
			tokens.push_back(parse_end_token());
		} else {
			tokens.push_back(parse_single_token());
		}
	}
	return tokens;
}

bool
IRC::CmdParser::is_at_end() {
	return m_current >= m_request.length();
}

std::string
IRC::CmdParser::parse_single_token() {
	while (!isspace(peek()) && !is_at_end())
			advance();
	std::string token = m_request.substr(m_start, m_current - m_start);
	m_start = m_current;
	return token;
}

std::string
IRC::CmdParser::parse_end_token(){
	while (!is_at_end())
		advance();
	std::string token = m_request.substr(m_start, m_current - m_start);
	m_start = m_current;
	return token;
}

bool
IRC::CmdParser::skip_space() {
	while (isspace(peek()) && !is_at_end())
		advance();
	m_start = m_current;
	return is_at_end();
}

char
IRC::CmdParser::peek(){
	if (is_at_end())
		return '\0';
	return m_request[m_current];
}

char
IRC::CmdParser::advance() {
	return m_request[m_current++];
}