/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:20:16 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/11 02:46:52 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tony on 29/03/2022.
//

#include "../include/Utils.hpp"
#include <iostream>

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

std::string
ft::popfirst(std::string const &s){
	if ( s.length() == 0 )
		return s;
	return s.substr(1, s.length() - 1);
}

std::string
ft::poplast(std::string const &s){
	if ( s.length() == 0 )
		return s;
	return s.substr(0, s.length() - 1);
}

void
ft::remove(std::vector<std::string> &v, std::string const &val){
	v.erase(std::remove(v.begin(), v.end(), val), v.end());
}

void
ft::debug_notice(std::string const &msg){
	std::cout << "NOTICE: " << msg << std::endl;
}

/**
 * Wildcard matching function from
 * http://www.drdobbs.com/architecture-and-design/matching-wildcards-an-empirical-way-to-t/240169123
 * 
 * Adapted for C++ string.
 */
bool
ft::match(std::string const &tame, std::string const &wild) {
	std::string::const_iterator tame_it = tame.begin();
	std::string::const_iterator wild_it = wild.begin();
	std::string::const_iterator tame_bookmark = tame.end();
	std::string::const_iterator wild_bookmark = wild.end();

	while ( true ){
		if ( *wild_it == '*' ){
			// Skip the wildcards
			while ( *++wild_it == '*' && wild_it != wild.end() );

			if ( wild_it == wild.end() )
				return true;

			if ( *wild_it != '?' ){
				while ( *tame_it != *wild_it ){
					if ( ++tame_it == tame.end() )
						return false;
				}
			}
			tame_bookmark = tame_it;
			wild_bookmark = wild_it;
		}
		else if ( *tame_it != *wild_it && *wild_it != '?' ){
			// No match, backup to one or bot bookmark's.
			if ( wild_bookmark != wild.end() ){
				if ( wild_it != wild_bookmark ){
					wild_it = wild_bookmark;

					if ( *tame_it != *wild_it ){
						tame_it = ++tame_bookmark;
						continue;
					}
					else {
						++wild_it;
					}
				}

				if ( tame_it != tame.end() ){
					tame_it++;
					continue;
				}
			}
			return false;
		}
		++tame_it;
		++wild_it;

		if ( tame_it == tame.end() ){
			while ( wild_it != wild.end() && *wild_it == '*' )
				wild_it++;

			if ( wild_it == wild.end() )
				return true;
			return false;
		}
	}
	return false;
}