/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:38:55 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/06 18:28:07 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

IRC::Channel::Channel() : m_users(), m_name(), m_mode() { }

IRC::Channel::Channel(std::string const &name, std::string const &pass, int mode) :
	m_users(),
	m_name(name),
	m_pass(pass),
	m_mode(mode) { }

IRC::Channel::Channel(Channel const &other) :
	m_users(other.m_users),
	m_name(other.m_name),
	m_pass(other.m_pass),
	m_mode(other.m_mode) { }

IRC::Channel &IRC::Channel::operator=(IRC::Channel const &other) {
	if ( &other == this )
		return *this;
	m_users = other.m_users;
	m_name = other.m_name;
	m_pass = other.m_pass;
	m_mode = other.m_mode;
	return *this;
}

IRC::Channel::~Channel() { }

void
IRC::Channel::set_name(std::string const &name) {
	m_name = name;
}

void
IRC::Channel::set_role(int mode) {
	m_mode = mode;
}

void
IRC::Channel::set_pass(std::string const &pass) {
	m_pass = pass;
}

std::string const&
IRC::Channel::get_name() const {
	return m_name;
}

int
IRC::Channel::get_mode() const {
	return m_mode;
}

std::string const&
IRC::Channel::get_pass() const {
	return m_pass;
}

void
IRC::Channel::subscribe(User *user){
	m_users.add(user);
}

void
IRC::Channel::unsubscribe(User *user){
	m_users.remove(user);
}

void
IRC::Channel::notify(std::string const &msg) {
	m_users.notify(msg);
}