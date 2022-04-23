/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actions.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:40:12 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 23:05:57 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Actions.hpp"

IRC::Actions::Actions() : m_actions() { }

IRC::Actions::Actions(Action unique) : m_actions()
{
	m_actions.push(unique);
}

IRC::Actions::Actions(Actions const &other) : m_actions(other.m_actions) { }

IRC::Actions&
IRC::Actions::operator=(Actions const &other) {
	if ( this == &other )
		return *this;
	m_actions = other.m_actions;
	return *this;
}

IRC::Actions::~Actions() { }

/**
 * Push
 * 
 * Push the parameter @param action into the action
 * queue.
 */
IRC::Actions&
IRC::Actions::push(Action action) {
	m_actions.push(action);
	return *this;
}

/**
 * Pop
 * 
 * Pop an action from the action queue.
 * If pop is called with a queue of size 0,
 * this will cause and undefined behaviour.
 */
IRC::Action
IRC::Actions::pop() {
	Action front = m_actions.front();

	m_actions.pop();
	return front;
}

/**
 * Empty
 * 
 * Returns true if actions queue is empty.
 * Otherwise false.
 */
bool
IRC::Actions::empty() const {
	return m_actions.empty();
}

/**
 * Unique_idle
 * 
 * Create an Actions with a unique action idle.
 */
IRC::Actions
IRC::Actions::unique_idle(){
	return Actions(Action::idle());
}

/**
 * Unique_send
 * 
 * Create an Actions with a unique action send.
 */
IRC::Actions
IRC::Actions::unique_send(User *user, std::string const &response){
	return Actions(Action::send(user, response));
}

/**
 * Unique_sendall
 * 
 * Create an Actions with a unique action sendall.
 */
IRC::Actions
IRC::Actions::unique_sendall(std::vector<User*> users, std::string const &response){
	return Actions(Action::sendall(users, response));
}

/**
 * Unique_ban
 * 
 * Create an Actions with a unique action ban.
 */
IRC::Actions
IRC::Actions::unique_ban(User *user){
	return Actions(Action::ban(user));
}

/**
 * Unique_banall
 * 
 * Create an Actions with a unique action banall.
 */
IRC::Actions
IRC::Actions::unique_banall(std::vector<User*> users){
	return Actions(Action::banall(users));
}

/**
 * Unique_disconnect
 * 
 * Create an Actions with a unique action disconnect.
 */
IRC::Actions
IRC::Actions::unique_disconnect(User *user){
	return Actions(Action::disconnect(user));
}

/**
 * Unique_disconnetall
 * 
 * Create an Actions with a unique action disconnectall.
 */
IRC::Actions
IRC::Actions::unique_disconnectall(std::vector<User*> users){
	return Actions(Action::disconnectall(users));
}
