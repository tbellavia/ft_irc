/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:43:10 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:52:40 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

IRC::User::User(Socket *socket, std::string const &pseudo, int role)
	: m_socket(socket), m_pseudo(pseudo), m_role(role) { }

IRC::User::User(IRC::User const &other)
	: m_socket(other.m_socket), m_pseudo(other.m_pseudo), m_role(other.m_role) { }

IRC::User&
IRC::User::operator=(IRC::User const &other) {
	if ( &other == this )
		return *this;
	m_socket = other.m_socket;
	m_pseudo = other.m_pseudo;
	m_role = other.m_role;
	return *this;
}

IRC::User::~User() { }

void
IRC::User::update(std::string const &msg) {
	m_socket->send(msg);
}

std::string const&
IRC::User::get_pseudo() const {
	return m_pseudo;
}

void
IRC::User::set_pseudo(std::string const &pseudo) {
	m_pseudo = pseudo;
}