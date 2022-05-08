/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:43:00 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 18:20:50 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Users.hpp"

IRC::Users::Users() : m_users() { }

IRC::Users::Users(Users const &other) : m_users(other.m_users) { }

IRC::Users &IRC::Users::operator=(Users const &other) {
	if ( this == &other )
		return *this;
	m_users = other.m_users;
	return *this;
}

IRC::Users::~Users() { }

void
IRC::Users::add(User *user) {
	if ( user != NULL ){
		m_users.insert(user);
	}
}

void
IRC::Users::remove(User *user) {
	if ( user != NULL ){
		m_users.erase(user);
	}
}

bool
IRC::Users::has(User *user) const {
	return m_users.count(user) == 1;
}

IRC::Action
IRC::Users::notify(std::string const &msg) {
	return Action::sendall(std::vector<User*>(m_users.begin(), m_users.end()), msg);
}
