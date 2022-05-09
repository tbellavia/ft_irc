/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:55:45 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:41:45 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACmd.hpp"

IRC::ACmd::ACmd(CmdCtx &ctx, std::string const &request) :
	m_ctx(ctx), m_request(request) { }

IRC::ACmd::ACmd(ACmd const &copy):
	m_ctx(copy.m_ctx), m_request(copy.m_request) { }

IRC::ACmd::~ACmd() { }

IRC::ACmd &IRC::ACmd::operator=(ACmd const &rhs) {
	if (this == &rhs)
		return *this;

	m_ctx = rhs.m_ctx;
	m_request = rhs.m_request;
	return *this;
}