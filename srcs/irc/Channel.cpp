/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:38:55 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 00:48:00 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

IRC::Channel::Channel() : m_users(), m_name(), m_mode() { }

IRC::Channel::Channel(std::string const &name, std::string const &pass, 
std::string const &topic, int mode) :
	m_users(),
	m_name(name),
	m_pass(pass),
	m_topic(topic),
	m_mode(mode) { }

IRC::Channel::Channel(Channel const &other) :
	m_users(other.m_users),
	m_name(other.m_name),
	m_pass(other.m_pass),
	m_topic(other.m_topic),
	m_mode(other.m_mode) { }

IRC::Channel &IRC::Channel::operator=(IRC::Channel const &other) {
	if ( &other == this )
		return *this;
	m_users = other.m_users;
	m_name = other.m_name;
	m_pass = other.m_pass;
	m_topic = other.m_topic;
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

void
IRC::Channel::set_topic(std::string const &topic) {
	m_topic = topic;
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

std::string const&
IRC::Channel::get_topic() const {
	return m_topic;
}

/**
 * Subscribe
 * 
 * Subscribe a user to channel.
 * If the password being passed match the password of channel,
 * it subscribe the user and returns True.
 * Otherwise it returns False without subscribing the user.
 * 
 */
bool
IRC::Channel::subscribe(User *user, std::string const &pass){
	if ( pass != m_pass )
		return false;
	m_users.add(user);
	return true;
}

void
IRC::Channel::unsubscribe(User *user){
	m_users.remove(user);
}

IRC::Action
IRC::Channel::notify(std::string const &msg) {
	return m_users.notify(msg);
}

bool
IRC::Channel::is_channel(std::string const &name) {
	return !name.empty() && (name[0] == '#' || name[0] == '&');
}

bool
IRC::Channel::is_valid(std::string const &name){
	return !name.empty() && is_channel(name) && is_chstring(name);
}