/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:13:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 11:39:34 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "App.hpp"

App::App() { }

App::~App() { }

void App::start(IRC::ConfigServer &config) const {
	IRC::Server server(config, true);
	IRC::Api api(config);

	server.serve_forever(api);
}