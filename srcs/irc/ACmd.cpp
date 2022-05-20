/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:55:45 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/19 12:12:52 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACmd.hpp"

IRC::ACmd::ACmd(
	CmdCtx &ctx, std::string const &request, std::string const &name
) :
		m_ctx(ctx),
		m_request(request),
		m_name(name),
		m_parser(request),
		m_arguments(m_parser.parse())
{
}

IRC::ACmd::ACmd(ACmd const &copy):
		m_ctx(copy.m_ctx),
		m_request(copy.m_request),
		m_name(copy.m_name),
		m_parser(copy.m_parser),
		m_arguments(copy.m_arguments)
{
}

IRC::ACmd::~ACmd()
{
}

std::vector<std::string>
IRC::ACmd::parse() {
	return m_parser.parse();
}

IRC::User *
IRC::ACmd::sender(){
	return m_ctx.sender;
}

IRC::Channels &
IRC::ACmd::channels(){
	return m_ctx.channels;
}

IRC::MasterUsers &
IRC::ACmd::users(){
	return m_ctx.users;
}

std::string	const &
IRC::ACmd::server_pass(){
	return m_ctx.config.server_pass;
}

std::string const &
IRC::ACmd::server_name(){
	return m_ctx.config.server_name;
}

IRC::ACmd &
IRC::ACmd::operator=(IRC::ACmd const &rhs)
{
	if (this == &rhs)
		return *this;

	m_ctx = rhs.m_ctx;
	m_request = rhs.m_request;
	m_name = rhs.m_name;
	m_parser = rhs.m_parser;
	m_arguments = rhs.m_arguments;

	return *this;
}
