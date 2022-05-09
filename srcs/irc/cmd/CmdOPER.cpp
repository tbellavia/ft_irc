/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdOPER.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:16:49 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/05 15:51:09 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdOPER.hpp"
#include <iostream>

IRC::CmdOPER::CmdOPER(CmdCtx &ctx, std::string const &request) : 
	ACmd(ctx, request, "OPER") { }

IRC::CmdOPER::~CmdOPER() { }

/**
 * OPER
 * 
 *  Command: OPER
 *  Parameters: <user> <password>
 */
IRC::Actions
IRC::CmdOPER::execute() {
	User *user = m_ctx.sender;
	ReplyBuilder reply(this->server_name(), user);
	std::vector<std::string> args = this->parse();

	std::cout << "CmdOPER: " << m_request << std::endl;
	if ( !user->connected() ){
		return Actions::unique_idle();
	}
	if ( args.size() == 1 || args.size() != Expected_args(2) ){
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	}
	std::string oper_user = args[1];
	std::string oper_pass = args[2];

	if ( oper_user.empty() || oper_pass.empty() ){
		return Actions::unique_send(user, reply.error_no_oper_host());
	}
	std::cout << "HERE" << std::endl;
	if ( oper_user != m_ctx.config.oper_name || oper_pass != m_ctx.config.oper_pass ){
		return Actions::unique_send(user, reply.error_password_mismatch());
	}
	// Set operator mode
	user->set_mode(MODE_OPERATOR);
	return Actions::unique_send(user, reply.reply_youre_oper());
}