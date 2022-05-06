/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:19:21 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 00:52:48 by bbellavi         ###   ########.fr       */
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

void
IRC::Channels::remove_user(User *user){
	std::map<std::string, Channel>::iterator it;

	for ( ; it != m_channels.end() ; ++it ){
		it->second.unsubscribe(user);
	}
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