/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:13:59 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 17:33:05 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Action.hpp"

IRC::Action::Action() : m_event(), m_sockets(), m_response() { }

IRC::Action::Action(int event) : m_event(event), m_sockets(), m_response() { }

IRC::Action::Action(int event, User *user, std::string const &response) :
	m_event(event),
	m_sockets(),
	m_response(response)
{
	m_sockets.push_back(user->get_socket());
}

IRC::Action::Action(int event, std::vector<User*> users, std::string const &response) :
	m_event(event),
	m_sockets(),
	m_response(response)
{
	std::vector<User*>::iterator it = users.begin();

	for ( ; it != users.end() ; ++it ){
		m_sockets.push_back((*it)->get_socket());
	}
}

IRC::Action::Action(Action const &other) :
	m_event(other.m_event),
	m_sockets(other.m_sockets),
	m_response(other.m_response) { }

IRC::Action&
IRC::Action::operator=(Action const &other) {
	if ( this == &other )
		return *this;
	m_response = other.m_response;
	m_event = other.m_event;
	m_sockets = other.m_sockets;
	return *this;
}

IRC::Action::~Action() { }

int
IRC::Action::event() const {
	return m_event;
}

bool
IRC::Action::isset(int event) const {
	return m_event == event;
}

std::vector<Socket*>
IRC::Action::sockets() const {
	return m_sockets;
}

std::string const&
IRC::Action::response() const {
	return m_response;
}

void
IRC::Action::add(User *user) {
	m_sockets.push_back(user->get_socket());
}

IRC::Action
IRC::Action::idle() {
	return Action(Event::IDLE);
}

IRC::Action
IRC::Action::send(User *user, std::string const &response) {
	return Action(Event::SEND, user, response);
}

IRC::Action
IRC::Action::sendall(std::vector<User*> users, std::string const &response){
	return Action(Event::SEND, users, response);
}

IRC::Action
IRC::Action::ban(User *user){
	return Action(Event::BAN, user);
}

IRC::Action
IRC::Action::banall(std::vector<User*> users){
	return Action(Event::BAN, users);
}

IRC::Action
IRC::Action::disconnect(User *user){
	return Action(Event::DISCONNECT, user);
}

IRC::Action
IRC::Action::disconnectall(std::vector<User*> users){
	return Action(Event::DISCONNECT, users);
}
