/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:55:45 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 21:57:40 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACmd.hpp"

IRC::ACmd::ACmd(CmdCtx &ctx, std::string const &request) :
	m_ctx(ctx), m_request(request) { }

IRC::ACmd::~ACmd() { }