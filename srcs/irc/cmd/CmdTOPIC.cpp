/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTOPIC.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:00:36 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/06 14:43:59 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdTOPIC.hpp"

IRC::CmdTOPIC::CmdTOPIC(CmdCtx &ctx, std::string const &request)
	: ACmd(ctx, request, "TOPIC") { }

IRC::CmdTOPIC::~CmdTOPIC() { }

IRC::Actions
IRC::CmdTOPIC::execute() {
	User			*target = this->sender();
	ReplyBuilder	reply(this->server_name(), target);
	Actions			actions;

	if ( !target->connected() )
		return Actions::unique_idle();
	if ( m_arguments.size() < Expected_args(1) || m_arguments.size() > Expected_args(2))
		return Actions::unique_send(target, reply.error_need_more_params(m_name));
	return Actions::unique_idle();
}