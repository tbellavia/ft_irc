/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:36:26 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/04 19:24:20 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "User.hpp"
# include "Network.hpp"

IRC::User::User() : 
	m_username(),
	m_nickname(),
	m_realname(),
	m_mode(MODE_RESTRICTED),
	m_socket(NULL) { }

IRC::User::User(std::string const &pseudo, std::string const &nick, 
	std::string const &realname, int mode, Socket *socket) : 
	m_username(pseudo),
	m_nickname(nick),
	m_realname(realname),
	m_mode(mode),
	m_socket(socket) { }

IRC::User::User(Socket *socket) : 
	m_username(),
	m_nickname(),
	m_realname(),
	m_mode(MODE_RESTRICTED),
	m_socket(socket) { }

IRC::User::User(IRC::User const &other) : 
	m_username(other.m_username), 
	m_nickname(other.m_nickname), 
	m_realname(other.m_realname),
	m_mode(other.m_mode), 
	m_socket(other.m_socket) { }

IRC::User &IRC::User::operator=(IRC::User const &other) {
	if ( &other == this )
		return *this;
	m_username = other.m_username;
	m_nickname = other.m_nickname;
	m_realname = other.m_realname;
	m_mode = other.m_mode;
	m_socket = other.m_socket;
	return *this;
}

IRC::User::~User() { }

void
IRC::User::set_username(std::string const &pseudo) {
	m_username = pseudo;
}

void
IRC::User::set_nickname(std::string const &nick) {
	m_nickname = nick;
}

void
IRC::User::set_realname(std::string const &realname){
	m_realname = realname;
}

void
IRC::User::set_mode(int mode) {
	m_mode |= mode;
}

void
IRC::User::set_socket(Socket *socket) {
	m_socket = socket;
}

void
IRC::User::unset_mode(int mode) {
	m_mode &= ~mode;
}

std::string const&
IRC::User::get_username() const {
	return m_username;
}

std::string const&
IRC::User::get_nick() const {
	return m_nickname;
}

std::string const&
IRC::User::get_realname() const {
	return m_realname;
}

int
IRC::User::get_mode() const {
	return m_mode;
}

Socket*
IRC::User::get_socket() {
	return m_socket;
}

bool
IRC::User::mode_isset(int mode) const {
	return m_mode & mode;
}

bool
IRC::User::connected() const {
	return !mode_isset(MODE_RESTRICTED);
}

bool
IRC::User::connection_complete() const {
	return mode_isset(MODE_PASS_) && mode_isset(MODE_NICK_) && mode_isset(MODE_USER_);
}

bool
IRC::User::pass_accepted() const {
	return mode_isset(MODE_PASS_);
}

void
IRC::User::update(std::string const &msg) {
	m_socket->send(net::ston(msg));
}

IRC::User::PseudoSelector::PseudoSelector(std::string const &pseudo) :
	m_pseudo(pseudo) { }

IRC::User::NickSelector::NickSelector(std::string const &nickname) :
	m_nickname(nickname) { }

IRC::User::ModeSelector::ModeSelector(int mode) :
	m_mode(mode) { }

IRC::User::SocketSelector::SocketSelector(Socket *socket) :
	m_socket(socket) { }

bool
IRC::User::PseudoSelector::operator()(User *user){
	return user->get_username() == m_pseudo;
}

bool
IRC::User::NickSelector::operator()(User *user){
	return user->get_nick() == m_nickname;
}

bool
IRC::User::ModeSelector::operator()(User *user){
	return user->mode_isset(m_mode);
}

bool
IRC::User::SocketSelector::operator()(User *user){
	return user->get_socket() == m_socket;
}