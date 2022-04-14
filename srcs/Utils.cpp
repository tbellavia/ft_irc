/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:20:16 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/14 23:35:50 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tony on 29/03/2022.
//

#include "../include/Utils.hpp"

bool ft::ends_with(const std::string &val, const std::string &ending) {
	if ( ending.size() > val.size() )
		return false;
	return std::equal(ending.rbegin(), ending.rend(), val.rbegin());
}

std::vector<std::string> ft::split(const std::string &s, const std::string &delim) {
	std::vector<std::string>	strings;
	std::string					rest;
	size_t						pos;

	rest = s;
	while ( (pos = rest.find(delim)) != std::string::npos ){
		strings.push_back(rest.substr(0, pos));
		rest = rest.substr(pos + delim.length(), rest.length());
	}
	strings.push_back(rest);
	return strings;
}

std::vector<std::string>
ft::split_one(std::string const &s, std::string const &delim) {
	std::vector<std::string> res;
	size_t pos;

	pos = s.find(delim);
	if ( pos == std::string::npos ) {
		res.push_back(s);
	} else {
		res.push_back(s.substr(0, pos));
		res.push_back(s.substr(pos + delim.length(), s.length()));
	}
	return res;
}
