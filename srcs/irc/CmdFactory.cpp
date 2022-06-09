/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:07:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/09 13:57:36 by lperson-         ###   ########.fr       */
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
	m_callbacks.insert(
		std::make_pair("INVITE", &CmdFactory::create_invite_cmd)
	);
	m_callbacks.insert(std::make_pair("KICK", &CmdFactory::create_kick_cmd));
	m_callbacks.insert(std::make_pair("WHO", &CmdFactory::create_who_cmd));
	m_callbacks.insert(std::make_pair("PING", &CmdFactory::create_ping_cmd));
	m_callbacks.insert(std::make_pair("PONG", &CmdFactory::create_pong_cmd));
	m_callbacks.insert(std::make_pair("QUIT", &CmdFactory::create_quit_cmd));
	m_callbacks.insert(std::make_pair("MODE", &CmdFactory::create_mode_cmd));
	m_callbacks.insert(std::make_pair("PART", &CmdFactory::create_part_cmd));
	m_callbacks.insert(std::make_pair("TOPIC", &CmdFactory::create_topic_cmd));
	// Both PRIVMSG and NOTICE are the same
	m_callbacks.insert(std::make_pair("PRIVMSG", &CmdFactory::create_privmsg_cmd));
	m_callbacks.insert(std::make_pair("NOTICE", &CmdFactory::create_privmsg_cmd));
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
IRC::CmdFactory::create_ping_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPING(ctx, request);
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

IRC::ACmd*
IRC::CmdFactory::create_invite_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdINVITE(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_kick_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdKICK(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_who_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdWHO(ctx, request);
}

IRC::ACmd *
IRC::CmdFactory::create_mode_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdMODE(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_privmsg_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPRIVMSG(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_part_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdPART(ctx, request);
}

IRC::ACmd*
IRC::CmdFactory::create_topic_cmd(CmdCtx &ctx, std::string const &request) {
	return new CmdTOPIC(ctx, request);
}