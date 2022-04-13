/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:54 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:43:59 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channels.hpp"

IRC::Channels::Channels() : m_channels() { }

// Should implement deep copy
IRC::Channels::Channels(Channels const &other) : m_channels(other.m_channels) { }

IRC::Channels
&IRC::Channels::operator=(IRC::Channels const &other) {
	if ( &other == this )
		return *this;
	m_channels = other.m_channels;
	return *this;
}

IRC::Channels::~Channels() {
	std::map<std::string, Channel*>::iterator it = m_channels.begin();

	for ( ; it != m_channels.end() ; ++it ){
		delete it->second;
	}
}

void
IRC::Channels::add(std::string const &name) {
	m_channels.insert( std::make_pair(name, new Channel(name)) );
}

void
IRC::Channels::remove(std::string const &name) {
	m_channels.erase( name );
}