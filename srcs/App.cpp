/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:13:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 08:43:31 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "App.hpp"

App::App() { }

App::App(App const &) { }

App::~App() { }

App &App::operator=(App const &) { return *this; }

void App::start(std::string const &port, std::string const &password) const {
	IRC::Server server("127.0.0.1", port, password, true);
	IRC::Api api(password);

	server.serve_forever(api);
}