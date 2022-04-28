/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 02:13:43 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/28 02:20:29 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdParser.hpp"


IRC::CommandParser::CommandParser(std::string const &request) : 
	m_request(request),
	m_start(0),
	m_current(0) { }

std::vector<std::string>
IRC::CommandParser::parse() {
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
IRC::CommandParser::is_at_end() {
	return m_current >= m_request.length();
}

std::string
IRC::CommandParser::parse_single_token() {
	if ( peek() == ':' )
		m_start++;
	while (!isspace(peek()) && !is_at_end())
			advance();
	std::string token = m_request.substr(m_start, m_current - m_start);
	m_start = m_current;
	return token;
}

std::string
IRC::CommandParser::parse_end_token(){
	while (!is_at_end())
		advance();
	std::string token = m_request.substr(m_start + 1, m_current - m_start + 1);
	m_start = m_current;
	return token;
}

bool
IRC::CommandParser::skip_space() {
	while (isspace(peek()) && !is_at_end())
		advance();
	m_start = m_current;
	return is_at_end();
}

char
IRC::CommandParser::peek(){
	if (is_at_end())
		return '\0';
	return m_request[m_current];
}

char
IRC::CommandParser::advance() {
	return m_request[m_current++];
}