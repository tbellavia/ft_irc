/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Masks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:56:31 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/27 22:01:11 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Masks.hpp"

bool
IRC::is_valid_mask(std::string const &mask) {
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