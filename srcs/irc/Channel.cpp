/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:38:55 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/13 15:05:58 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include "Channel.hpp"
#include "Masks.hpp"

IRC::Channel::Channel() : 
	m_users(), 
	m_voices(),
	m_invites(),
	m_operators(),
	m_creator(NULL),
	m_ban_masks(),
	m_name(),
	m_key(NULL),
	m_limit(-1),
	m_topic(),
	m_mode(0) { }

IRC::Channel::Channel(std::string const &name, User *creator, int mode) :
	m_users(), 
	m_voices(),
	m_invites(),
	m_operators(),
	m_creator(creator),
	m_ban_masks(),
	m_name(name),
	m_key(NULL),
	m_limit(-1),
	m_topic(),
	m_mode(mode) { }

IRC::Channel::Channel(Channel const &other) :
	m_users(other.m_users),
	m_voices(other.m_voices),
	m_invites(other.m_invites),
	m_operators(other.m_operators),
	m_creator(other.m_creator),
	m_ban_masks(other.m_ban_masks),
	m_name(other.m_name),
	m_key(NULL),
	m_limit(other.m_limit),
	m_topic(other.m_topic),
	m_mode(other.m_mode) {
	if (other.m_key)
		m_key = new std::string(*other.m_key);
}

IRC::Channel &IRC::Channel::operator=(IRC::Channel const &other) {
	if ( &other == this )
		return *this;
	m_users = other.m_users;
	m_voices = other.m_voices;
	m_invites = other.m_invites;
	m_operators = other.m_operators;
	m_creator = other.m_creator;
	m_ban_masks = other.m_ban_masks;
	m_name = other.m_name;
	if ( m_key )
		delete m_key;
	m_key = NULL;
	if ( other.m_key )
		m_key = new std::string(*other.m_key);
	m_limit = other.m_limit;
	m_topic = other.m_topic;
	m_mode = other.m_mode;
	return *this;
}

IRC::Channel::~Channel() {
	if ( m_key )
		delete m_key;
}

void
IRC::Channel::set_name(std::string const &name) {
	m_name = name;
}

void
IRC::Channel::set_mode(int mode) {
	m_mode |= mode;
}

void
IRC::Channel::unset_mode(int mode) {
	m_mode &= ~mode;
}

void
IRC::Channel::set_key(std::string const &pass) {
	if ( m_key )
		delete m_key;
	m_key = new std::string(pass);
}

void
IRC::Channel::unset_key(std::string const &pass) {
	if ( m_key && *m_key == pass ) {
		delete m_key;
		m_key = NULL;
	}
}

void
IRC::Channel::set_limit(int limit) {
	m_limit = limit;
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

std::string
IRC::Channel::get_mode_string() const {
	std::string const mode_string = IRC_CHANNEL_MODE_STRING;
	std::string reply;
	for (std::string::size_type i = 0 ; i < mode_string.length(); ++i)
	{
		if (this->get_mode() & (0x01 << i))
			reply += mode_string[i];
	}
	return reply;
}

std::string const*
IRC::Channel::get_key() const {
	return m_key;
}

int
IRC::Channel::get_limit() const {
	return m_limit;
}

std::string const&
IRC::Channel::get_topic() const {
	return m_topic;
}

std::vector<std::string> const&
IRC::Channel::get_ban_masks() const {
	return m_ban_masks;
}

bool
IRC::Channel::is_user(User *user) const {
	return m_users.has(user);
}

bool
IRC::Channel::is_banned_user(User *user) const {
	for ( std::size_t i = 0; i < m_ban_masks.size(); ++i ) {
		if ( user->mask_match(m_ban_masks[i]) )
			return true;
	}
	return false;
}

bool
IRC::Channel::is_invited_user(User *user) const{
	return m_invites.has(user);
}

bool
IRC::Channel::is_operator_user(User *user) const{
	return user == m_creator || m_operators.has(user);
}

bool
IRC::Channel::is_voices_user(User *user) const{
	return m_voices.has(user);
}


/**
 * Check if user has correct rights to send message on channel.
 */
bool
IRC::Channel::is_authorized(User *user) const {
	if ( is_banned_user(user) )
		return false;
	// Check outside message disable
	if ( is_outside_disable() && !is_user(user) )
		return false;
	// Check if authorized to speak in channel
	if ( is_moderated() && !(is_voices_user(user) || is_operator_user(user)) )
		return false;
	return true;
}

bool
IRC::Channel::equal_key(std::string const &key) const {
	return m_key && *m_key == key;
}

/**
 * Iterators and getters to iterate through channel users
*/

IRC::Channel::iterator
IRC::Channel::find(User *to_find) {
	return m_users.find(to_find);
}

IRC::Channel::const_iterator
IRC::Channel::find(User *to_find) const {
	return m_users.find(to_find);
}

IRC::Channel::iterator
IRC::Channel::begin() {
	return m_users.begin();
}

IRC::Channel::const_iterator
IRC::Channel::begin() const {
	return m_users.begin();
}

IRC::Channel::iterator
IRC::Channel::end() {
	return m_users.end();
}

IRC::Channel::const_iterator
IRC::Channel::end() const {
	return m_users.end();
}

IRC::Channel::reverse_iterator
IRC::Channel::rbegin() {
	return m_users.rbegin();
}

IRC::Channel::const_reverse_iterator
IRC::Channel::rbegin() const {
	return m_users.rbegin();
}

IRC::Channel::reverse_iterator
IRC::Channel::rend() {
	return m_users.rend();
}

IRC::Channel::const_reverse_iterator
IRC::Channel::rend() const {
	return m_users.rend();
}

IRC::Users::view_type
IRC::Channel::get_users() {
	return m_users.get_view();
}

std::size_t
IRC::Channel::size() const {
	return m_users.size();
}

bool
IRC::Channel::empty() const {
	return m_users.empty();
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

void
IRC::Channel::setOperator(User *user) {
	m_operators.add(user);
}

void
IRC::Channel::addBanMask(std::string const &ban_mask) {
	m_ban_masks.push_back(ban_mask);
}

void
IRC::Channel::deleteBanMask(std::string const &ban_mask) {
	std::vector<std::string>::iterator it = std::find(
		m_ban_masks.begin(), m_ban_masks.end(), ban_mask
	);

	if (it != m_ban_masks.end())
		m_ban_masks.erase(it);
}

void
IRC::Channel::unsetOperator(User *user) {
	m_operators.remove(user);
}

void
IRC::Channel::allowVoice(User *user) {
	m_voices.add(user);
}

void
IRC::Channel::disallowVoice(User *user) {
	m_voices.remove(user);
}

void
IRC::Channel::inviteUser(User *user) {
	m_invites.add(user);
}

void
IRC::Channel::uninviteUser(User *user) {
	m_invites.remove(user);
}

IRC::Action
IRC::Channel::notify(std::string const &msg, User *sender) {
	// TODO: verify if sender has the correct rights
	return m_users.notify(msg, sender);
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
IRC::Channel::is_outside_disable() const {
	return m_mode & CHAN_MODE_NO_OUTSIDE_MESSAGE;
}

bool
IRC::Channel::is_channel_name(std::string const &name) {
	return !name.empty() && (name[0] == '#' || name[0] == '&');
}

bool
IRC::Channel::is_valid_name(std::string const &name){
	return !name.empty() && name.size() < 200 &&
			is_channel_name(name) && is_chstring(name);
}