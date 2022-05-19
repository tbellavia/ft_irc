/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUSER.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:53:55 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/19 11:47:47 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "CmdUSER.hpp"
#include "CmdParser.hpp"

IRC::CmdUSER::CmdUSER(CmdCtx &ctx, std::string const &request) : 
	ACmd(ctx, request, "USER") { }

IRC::CmdUSER::~CmdUSER() { }

IRC::Actions
IRC::CmdUSER::execute() {
	User *user = m_ctx.sender;
	std::vector<std::string> args = CmdParser(m_request).parse();
	ReplyBuilder reply(this->server_name(), user);

	// USER: <username> <hostname> <servername> <realname>
	// Example: 'USER' 'MielPops' '0' '*' ':realname' 
	// Ignore <hostname> and <servername>

	if ( user->connected() )
		return Actions::unique_idle();
	// Not enough parameters
	if ( args.size() == 1 || args.size() > Expected_args(4) )
		return Actions::unique_send(user, reply.error_need_more_params(m_name));
	// Already registered
	if ( user->mode_isset(MODE_USER_) )
		return Actions::unique_send(user, reply.error_already_registered());

	std::string username = args[1];
	std::string realname = args[4];

	if ( realname[0] == ':' )
		realname = ft::popfirst(realname);

	std::cout << "USER: \n\tUsername: " << username << "\n\tRealname: " << realname << std::endl;
	
	// Check username validity
	user->set_username(username);
	user->set_realname(realname);

	user->set_mode(MODE_USER_);

	// If user has completed connection, remove Restricted mode
	if ( user->connection_complete() ){
		std::cout << "Connection completed!" << std::endl;
		user->unset_mode(MODE_RESTRICTED_);
	}
	return Actions::unique_idle();
}