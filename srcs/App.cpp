/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:13:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/04 23:51:05 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "App.hpp"

App::App() { }

void App::start(std::string const &port, std::string const &password) const {
	IRC::ConfigServer config(
		password, "127.0.0.1", "ft.irc.com", port, "ft_oper", "ft_oper", 10);
	IRC::Server server(config, true);
	IRC::Api api(password);

	server.serve_forever(api);
}