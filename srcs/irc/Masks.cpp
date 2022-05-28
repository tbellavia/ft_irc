/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Masks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:56:31 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/28 23:56:07 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Masks.hpp"

bool
IRC::mask::is_valid(std::string const &mask) {
	std::string::const_iterator cursor = mask.begin();

	// Valid : #*.ltu or $*.edu
	if ( mask.length() < 4 )
		return false;
	if ( *cursor == MASK_SYM_HOST || *cursor == MASK_SYM_SERVER )
	{
		++cursor;
		// Skip all character that are not selector char
		while ( !IS_MASK_SELECTOR(*cursor) && cursor != mask.end() )
			++cursor;
		// Skip all selector character -> `*' and `?'
		while ( IS_MASK_SELECTOR(*cursor) && cursor != mask.end() )
			++cursor;
		// Skip all selector character except `.'
		while ( *cursor != '.' && cursor != mask.end() )
			++cursor;
		if ( cursor == mask.end() )
			return false;
		if ( *cursor != '.' )
			return false;
		for ( ; cursor != mask.end() ; ++cursor ){
			if ( IS_MASK_SELECTOR(*cursor) )
				return false;
		}
	}
	return true;
}

/**
 * Wildcard matching function from
 * http://www.drdobbs.com/architecture-and-design/matching-wildcards-an-empirical-way-to-t/240169123
 * 
 * Adapted for C++ string.
 */
bool
IRC::mask::match(std::string const &tame, std::string const &wild) {
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

bool
IRC::mask::is_host_mask(std::string const &mask) {
	if ( !mask.empty() )
		return mask[0] == MASK_SYM_HOST && 
			(mask.find(MASK_SYM_SELECTOR_ALL) != std::string::npos || 
			mask.find(MASK_SYM_SELECTOR_OPT) != std::string::npos);
	return false;
}

bool
IRC::mask::is_server_mask(std::string const &mask) {
	if ( !mask.empty() )
		return mask[0] == MASK_SYM_SERVER && (mask.find(MASK_SYM_SELECTOR_ALL) != std::string::npos || 
			mask.find(MASK_SYM_SELECTOR_OPT) != std::string::npos);
	return false;
}

bool
IRC::mask::is_server_or_host_mask(std::string const &mask) {
	return is_server_mask(mask) || is_host_mask(mask);
}