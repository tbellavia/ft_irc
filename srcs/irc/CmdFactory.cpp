/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:07:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/11 02:47:35 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdFactory.hpp"
#include <iostream>
// Use some macro shit to automatically create proto and definitions for commands ?

IRC::CmdFactory::CmdFactory() : ICmdFactory(), m_callbacks() 
{
	m_callbacks.insert(std::make_pair("PASS", &CmdFactory::create_pass_cmd));
	m_callbacks.insert(std::make_pair("NICK", &CmdFactory::create_nick_cmd));
	m_callbacks.insert(std::make_pair("USER", &CmdFactory::create_user_cmd));
	m_callbacks.insert(std::make_pair("OPER", &CmdFactory::create_oper_cmd));
	m_callbacks.insert(std::make_pair("JOIN", &CmdFactory::create_join_cmd));
	m_callbacks.insert(std::make_pair("PONG", &CmdFactory::create_pong_cmd));
	m_callbacks.insert(std::make_pair("QUIT", &CmdFactory::create_quit_cmd));
	m_callbacks.insert(std::make_pair("MODE", &CmdFactory::create_mode_cmd));
}

IRC::CmdFactory::CmdFactory(CmdFactory const &copy) :
	ICmdFactory(), m_callbacks(copy.m_callbacks) { }

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
IRC::CmdFactory::create_nick_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdNICK(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_user_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdUSER(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_pong_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPONG(ctx, request);
}


IRC::ACmd*
IRC::CmdFactory::create_quit_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdQUIT(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_oper_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdOPER(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_join_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdJOIN(ctx, request);
}

IRC::ACmd *
IRC::CmdFactory::create_mode_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdMODE(ctx, request);
}