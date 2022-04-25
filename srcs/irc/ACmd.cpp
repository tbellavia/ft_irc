/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:55:45 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/26 01:38:03 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACmd.hpp"

IRC::ACmd::ACmd(CmdCtx &ctx, std::string const &request, std::string const &name) :
	m_ctx(ctx), m_request(request), m_name(name) { }

IRC::ACmd::~ACmd() { }