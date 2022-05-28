/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:43:00 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/28 22:06:56 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Users.hpp"
# include "Masks.hpp"

IRC::Users::Users() : m_users() { }

IRC::Users::Users(Users const &other) : m_users(other.m_users) { }

IRC::Users::Users(MasterUsers const &other) : m_users() {
	std::map<int, User*> const &users = other.get_users();
	std::map<int, User*>::const_iterator it = users.begin();

	for ( ; it != users.end() ; ++it ){
		this->add(it->second);
	}
}

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

IRC::Users::view_type
IRC::Users::get_view(){
	return std::make_pair(m_users.begin(), m_users.end());
}

IRC::Users::const_view_type
IRC::Users::get_view() const{
	return std::make_pair(m_users.begin(), m_users.end());
}

IRC::Users::reverse_view_type
IRC::Users::get_rview(){
	return std::make_pair(m_users.rbegin(), m_users.rend());
}

IRC::Users::const_reverse_view_type
IRC::Users::get_rview() const{
	return std::make_pair(m_users.rbegin(), m_users.rend());
}

bool
IRC::Users::has(User *user) const {
	return m_users.count(user) == 1;
}

IRC::Users::iterator
IRC::Users::find(User *to_find) {
	return m_users.find(to_find);
}

IRC::Users::const_iterator
IRC::Users::find(User *to_find) const {
	return m_users.find(to_find);
}


/**
 * Notify all users except sender
 */
IRC::Action
IRC::Users::notify(std::string const &msg, User *sender) {
	Action action;
	view_type view = this->get_view();
	std::vector<User*> subscribers;

	// If no exception, send notify to all users.
	if ( sender == NULL )
		return Action::sendall(std::vector<User*>(view.first, view.second), msg);

	for ( ; view.first != view.second ; ++view.first ){
		User *user = *view.first;

		if ( user != sender )
			subscribers.push_back(user);
	}
	return Action::sendall(subscribers, msg);
}

/**
 * Notify users matching the host mask
 */
IRC::Action
IRC::Users::notify_host_mask(std::string const &msg, std::string const &mask, User *sender){
	Action action;
	view_type view = this->get_view();
	std::vector<User*> subscribers;
	// Remove `#' or `$' prefix
	std::string clean_mask = ft::popfirst(mask); 

	for ( ; view.first != view.second ; ++view.first ){
		User *user = *view.first;

		if ( mask::match(user->get_hostname(), clean_mask) && user != sender ){
			subscribers.push_back(user);
		}
	}
	return Action::sendall(subscribers, msg);
}

IRC::Users::iterator
IRC::Users::begin(){
	return m_users.begin();
}

IRC::Users::iterator 
IRC::Users::end(){
	return m_users.end();
}

IRC::Users::const_iterator 
IRC::Users::begin() const{
	return m_users.begin();
}

IRC::Users::const_iterator 
IRC::Users::end() const{
	return m_users.end();
}

IRC::Users::reverse_iterator 
IRC::Users::rbegin(){
	return m_users.rbegin();
}

IRC::Users::reverse_iterator 
IRC::Users::rend(){
	return m_users.rend();
}

IRC::Users::const_reverse_iterator 
IRC::Users::rbegin() const{
	return m_users.rbegin();
}

IRC::Users::const_reverse_iterator 
IRC::Users::rend() const{
	return m_users.rend();
}
