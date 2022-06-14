/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 23:28:20 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/08 11:20:42 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

# include <string>

namespace IRC
{
	struct ConfigServer {
		std::string server_pass;
		std::string server_host;
		std::string server_name;
		std::string server_port;
		std::string server_version;
		std::string server_creation_date;
		std::string oper_pass;
		std::string oper_name;
		int listen_max;

		ConfigServer(
			std::string const &server_pass_ = "",
			std::string const &server_host_ = "",
			std::string const &server_name_ = "",
			std::string const &server_port_ = "",
			std::string const &server_version = "",
			std::string const &oper_pass_ = "",
			std::string const &oper_name_ = "",
			int listen_max_ = 0
		);
		ConfigServer(ConfigServer const &other);
		ConfigServer &operator=(ConfigServer const &other);
		~ConfigServer();

		void update_creation_date();
	};
}


#endif
