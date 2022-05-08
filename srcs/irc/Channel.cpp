/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:38:55 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 18:31:17 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

IRC::Channel::Channel() : 
	m_users(), 
	m_voices(),
	m_bans(),
	m_invites(),
	m_operators(),
	m_creator(NULL),
	m_name(),
	m_key(),
	m_topic(),
	m_mode(CHAN_MODE_DEFAULT) { }

IRC::Channel::Channel(std::string const &name, User *creator, int mode) :
	m_users(), 
	m_voices(),
	m_bans(),
	m_invites(),
	m_operators(),
	m_creator(creator),
	m_name(name),
	m_key(),
	m_topic(),
	m_mode(mode) { }

IRC::Channel::Channel(Channel const &other) :
	m_users(other.m_users),
	m_voices(other.m_voices),
	m_bans(other.m_bans),
	m_invites(other.m_invites),
	m_operators(other.m_operators),
	m_creator(other.m_creator),
	m_name(other.m_name),
	m_key(other.m_key),
	m_topic(other.m_topic),
	m_mode(other.m_mode) { }

IRC::Channel &IRC::Channel::operator=(IRC::Channel const &other) {
	if ( &other == this )
		return *this;
	m_users = m_users;
	m_voices = m_voices;
	m_bans = m_bans;
	m_invites = m_invites;
	m_operators = m_operators;
	m_creator = m_creator;
	m_name = m_name;
	m_key = m_key;
	m_topic = m_topic;
	m_mode = m_mode;
	return *this;
}

IRC::Channel::~Channel() { }

void
IRC::Channel::set_name(std::string const &name) {
	m_name = name;
}

void
IRC::Channel::set_mode(int mode) {
	m_mode = mode;
}

void
IRC::Channel::set_key(std::string const &pass) {
	m_key = pass;
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
IRC::Channel::get_key() const {
	return m_key;
}

std::string const&
IRC::Channel::get_topic() const {
	return m_topic;
}

bool
IRC::Channel::is_banned(User *user) const {
	return m_bans.has(user);
}

bool
IRC::Channel::is_invite(User *user) const{
	return m_invites.has(user);
}

bool
IRC::Channel::is_operator(User *user) const{
	return m_operators.has(user);
}

bool
IRC::Channel::is_voices(User *user) const{
	return m_voices.has(user);
}

bool
IRC::Channel::equal_key(std::string const &key) const {
	return m_key == key;
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
void
IRC::Channel::subscribe(User *user){
	m_users.add(user);
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
IRC::Channel::is_default() const {
	return m_mode & CHAN_MODE_DEFAULT;
}

bool
IRC::Channel::is_private() const {
	return m_mode & CHAN_MODE_PRIVATE;
}

bool
IRC::Channel::is_secret() const {
	return m_mode & CHAN_MODE_SECRET;
}

bool
IRC::Channel::is_invite() const {
	return m_mode & CHAN_MODE_INVITE;
}

bool
IRC::Channel::is_moderated() const {
	return m_mode & CHAN_MODE_MODERATED;
}

bool
IRC::Channel::is_channel(std::string const &name) {
	return !name.empty() && (name[0] == '#' || name[0] == '&');
}

bool
IRC::Channel::is_valid(std::string const &name){
	return !name.empty() && is_channel(name) && is_chstring(name);
}