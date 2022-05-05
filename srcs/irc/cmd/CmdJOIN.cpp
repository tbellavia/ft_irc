/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:53:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/05 23:09:05 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdJOIN.hpp"
#include <iostream>

IRC::CmdJOIN::CmdJOIN(CmdCtx &ctx, std::string const &request) :
	ACmd(ctx, request, "JOIN") { }

IRC::CmdJOIN::~CmdJOIN() { }

IRC::Actions
IRC::CmdJOIN::execute() {
	// User *user = m_ctx.sender;
	std::vector<std::string> args = this->parse();

	std::cout << "CmdJOIN: ";
	for ( auto arg : args ){
		std::cout << arg << " | ";
	}
	std::cout << std::endl;
	return Actions::unique_idle();
}