/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:31:10 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/04 23:44:27 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

IRC::ConfigServer::ConfigServer(
	std::string const &server_pass_,
	std::string const &server_host_,
	std::string const &server_name_,
	std::string const &server_port_,
	std::string const &oper_pass_,
	std::string const &oper_name_,
	int listen_max_
) :
	server_pass(server_pass_),
	server_host(server_host_),
	server_name(server_name_),
	server_port(server_port_),
	oper_pass(oper_pass_),
	oper_name(oper_name_),
	listen_max(listen_max_) { }

IRC::ConfigServer::ConfigServer(ConfigServer const &other) : 
	server_pass(other.server_pass),
	server_host(other.server_host),
	server_name(other.server_name),
	server_port(other.server_port),
	oper_pass(other.oper_pass),
	oper_name(other.oper_name),
	listen_max(other.listen_max) {}

IRC::ConfigServer&
IRC::ConfigServer::operator=(ConfigServer const &other){
	if ( this == &other )
		return *this;
	server_pass = other.server_pass;
	server_host = other.server_host;
	server_name = other.server_name;
	server_port = other.server_port;
	oper_pass = other.oper_pass;
	oper_name = other.oper_name;
	listen_max = other.listen_max;
	return *this;
}

IRC::ConfigServer::~ConfigServer() { }