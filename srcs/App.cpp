/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:13:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 13:58:36 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "App.hpp"

App::App() { }

void App::start(std::string const &port, std::string const &password) const {
    IRC::Server server("127.0.0.1", port, password, true);
    IRC::Api api;

    server.serve_forever(api);
}