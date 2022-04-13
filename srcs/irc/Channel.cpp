/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:37:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:43:03 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

IRC::Channel::Channel(std::string const &name) 
	: m_name(name), m_subscribers() { }

IRC::Channel::Channel(IRC::Channel const &other) 
	: m_name(other.m_name), m_subscribers(other.m_subscribers) { }

IRC::Channel&
IRC::Channel::operator=(IRC::Channel const &other) {
	if ( this == &other )
		return *this;
	m_name = other.m_name;
	m_subscribers = other.m_subscribers;
	return *this;
}

IRC::Channel::~Channel() { }

void
IRC::Channel::subscribe(User *user) {
	m_subscribers.insert(user);
}

void
IRC::Channel::unsubscribe(User *user) {
	m_subscribers.erase(user);
}

void
IRC::Channel::notify(std::string const &msg){
	// Notify all user for now, but probably need to except the Sender (see RFC 1258 or 1459)
	for ( std::set<IRC::User*>::iterator it = m_subscribers.begin() ; it != m_subscribers.end() ; ++it ){
		(*it)->update(msg);
	}
}