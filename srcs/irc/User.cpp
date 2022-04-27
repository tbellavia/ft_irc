/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:36:26 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 02:53:00 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "User.hpp"
# include "Network.hpp"

IRC::User::User() : 
	m_pseudo(),
	m_nickname(),
	m_mode(MODE_ONBOARD),
	m_socket(NULL) { }

IRC::User::User(std::string const &pseudo, std::string const &nick, int mode, Socket *socket) : 
	m_pseudo(pseudo),
	m_nickname(nick),
	m_mode(mode),
	m_socket(socket) { }

IRC::User::User(Socket *socket) : 
	m_pseudo(),
	m_nickname(),
	m_mode(MODE_ONBOARD),
	m_socket(socket) { }

IRC::User::User(IRC::User const &other) : 
	m_pseudo(other.m_pseudo), 
	m_nickname(other.m_nickname), 
	m_mode(other.m_mode), 
	m_socket(other.m_socket) { }

IRC::User &IRC::User::operator=(IRC::User const &other) {
	if ( &other == this )
		return *this;
	m_pseudo = other.m_pseudo;
	m_nickname = other.m_nickname;
	m_mode = other.m_mode;
	m_socket = other.m_socket;
	return *this;
}

IRC::User::~User() { }

void
IRC::User::set_pseudo(std::string const &pseudo) {
	m_pseudo = pseudo;
}

void
IRC::User::set_nick(std::string const &nick) {
	m_nickname = nick;
}

void
IRC::User::set_mode(int mode) {
	m_mode = mode;
}

void
IRC::User::set_socket(Socket *socket) {
	m_socket = socket;
}

std::string const&
IRC::User::get_pseudo() const {
	return m_pseudo;
}

std::string const&
IRC::User::get_nick() const {
	return m_nickname;
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
IRC::User::mode_isset(int mode){
	return m_mode & mode;
}

bool
IRC::User::connected() const {
	return !(m_mode & MODE_ONBOARD);
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
	return user->get_pseudo() == m_pseudo;
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