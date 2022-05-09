/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:07:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:37:33 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdFactory.hpp"
#include <iostream>
// Use some macro shit to automatically create proto and definitions for commands ?

IRC::CmdFactory::CmdFactory() : ICmdFactory(), m_callbacks() 
{
	m_callbacks.insert(std::make_pair("PASS", &CmdFactory::create_pass_cmd));
	m_callbacks.insert(std::make_pair("PONG", &CmdFactory::create_pong_cmd));
	m_callbacks.insert(std::make_pair("NICK", &CmdFactory::create_nick_cmd));
	m_callbacks.insert(std::make_pair("QUIT", &CmdFactory::create_quit_cmd));
}

IRC::CmdFactory::CmdFactory(CmdFactory const &copy):
	m_callbacks(copy.m_callbacks) { }

IRC::CmdFactory::~CmdFactory() { }

IRC::ACmd*
IRC::CmdFactory::create_cmd(CmdCtx &ctx, std::string const &request) {
	std::map<std::string, callback_t>::iterator found;
	std::string command = ft::split_one(request)[0];

	std::cout << "COMMAND: " << command << std::endl;
	if ( (found = m_callbacks.find(command)) != m_callbacks.end() ){
		return (this->*found->second)(ctx, request);
	}
	return NULL;
}

IRC::ACmd*
IRC::CmdFactory::create_pass_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPASS(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_pong_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPONG(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_nick_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdNICK(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_quit_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdQUIT(ctx, request);
}

IRC::CmdFactory &IRC::CmdFactory::operator=(CmdFactory const &rhs) {
	if (this == &rhs)
		return *this;

	m_callbacks = rhs.m_callbacks;
	return *this;
}