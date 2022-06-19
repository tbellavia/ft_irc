/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:19:21 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/19 23:09:48 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channels.hpp"

IRC::Channels::Channels() : m_channels() { }

IRC::Channels::~Channels() { }

/**
 * Add
 * 
 * Add a channel to the channels list.
 */
void
IRC::Channels::add(Channel const &channel) {
	m_channels.insert(std::make_pair(
		channel.get_name(),
		channel
	));
}

/**
 * Remove
 * 
 * Remove a channel from the channels list.
 */
void
IRC::Channels::remove(std::string const &name) {
	std::map<std::string, Channel>::iterator found = m_channels.find(name);

	if ( found != m_channels.end() ){
		m_channels.erase(found);
	}
}

/**
 * Has
 * 
 * Check whether the channel is in the channel list.
 */
bool
IRC::Channels::has(std::string const &name) {
	return m_channels.count(name) == 1;
}


/**
 * Find
 * 
 * Find a channel by its name.
 */
IRC::Channel*
IRC::Channels::find(std::string const &name) {
	std::map<std::string, Channel>::iterator found = m_channels.find(
		ft::string_tolower(name)
	);
	if ( found == m_channels.end() )
		found = m_channels.find(ft::string_toupper(name));

	if ( found != m_channels.end() )
		return &found->second;
	return NULL;
}

void
IRC::Channels::remove_user(User *user){
	std::map<std::string, Channel>::iterator it = m_channels.begin();
	std::map<std::string, Channel>::iterator itNext;

	for ( ; it != m_channels.end() ; it = itNext ){
		it->second.unsubscribe(user);
		itNext = it;
		++itNext;
		if (it->second.empty()) {
			m_channels.erase(it->first);
		}
	}
}

/**
 * Returns the first Channel where user is present.
 */
IRC::Channel*
IRC::Channels::find_by_user(User *user) {
	std::map<std::string, Channel>::reverse_iterator it = m_channels.rbegin();

	for ( ; it != m_channels.rend() ; ++it ){
		if ( (*it).second.is_user(user) )
			return &it->second;
	}
	return NULL;
}

/**
 * Returns a list of channels where user has subscribed to.
 */
std::vector<IRC::Channel*>
IRC::Channels::get_channels_by_user(User *user) {
	std::vector<IRC::Channel*> channels;
	std::map<std::string, Channel>::iterator it = m_channels.begin();

	for ( ; it != m_channels.end() ; ++it ){
		if ( it->second.is_user(user) ){
			channels.push_back(&it->second);
		}
	}
	return channels;
}

/**
 * Notify all channels the `user' has subscribed to.
 * 
 */
IRC::Actions
IRC::Channels::notify_by_user(User *user, std::string const &message) {
	std::map<std::string, Channel>::iterator it = m_channels.begin();
	Actions actions;

	for ( ; it != m_channels.end() ; ++it ){
		if ( it->second.is_user(user) ){
			actions.push(it->second.notify(message, user));
		}
	}
	return actions;
}

/**
 * Get channels
 * 
 * Get a vector of all the channels.
 */
std::vector<IRC::Channel>
IRC::Channels::get_channels() {
	std::map<std::string, Channel>::iterator it;
	std::vector<Channel> channels;

	for ( it = m_channels.begin() ; it != m_channels.end() ; ++it ) {
		channels.push_back( it->second );
	}
	return channels;
}