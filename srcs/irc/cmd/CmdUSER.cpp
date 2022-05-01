/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUSER.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:53:55 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/01 19:21:28 by bbellavi         ###   ########.fr       */
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
	std::vector<std::string> args = CmdParser(m_request).parse();
	// std::vector<std::string> args = this->get_arguments();

	// Not enough parameters
	// Already registered
	for ( auto arg : args ){
		std::cout << "'" << arg << "' ";
	}
	std::cout << std::endl;
	return Actions::unique_idle();
}