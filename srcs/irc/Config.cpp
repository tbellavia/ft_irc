/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:31:10 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/08 10:32:43 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include <ctime>

IRC::ConfigServer::ConfigServer(
	std::string const &server_pass_,
	std::string const &server_host_,
	std::string const &server_name_,
	std::string const &server_port_,
	std::string const &server_version_,
	std::string const &oper_pass_,
	std::string const &oper_name_,
	int listen_max_
) :
	server_pass(server_pass_),
	server_host(server_host_),
	server_name(server_name_),
	server_port(server_port_),
	server_version(server_version_),
	server_creation_date(),
	oper_pass(oper_pass_),
	oper_name(oper_name_),
	listen_max(listen_max_) { }

IRC::ConfigServer::ConfigServer(ConfigServer const &other) : 
	server_pass(other.server_pass),
	server_host(other.server_host),
	server_name(other.server_name),
	server_port(other.server_port),
	server_version(other.server_version),
	server_creation_date(other.server_creation_date),
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
	server_version = other.server_version;
	server_creation_date = other.server_creation_date;
	oper_pass = other.oper_pass;
	oper_name = other.oper_name;
	listen_max = other.listen_max;
	return *this;
}

IRC::ConfigServer::~ConfigServer() { }

void IRC::ConfigServer::update_creation_date() {
	std::time_t now = std::time(NULL);
	struct tm *time_info = std::localtime(&now);
	server_creation_date = std::asctime(time_info);
}
