/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:19:24 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 00:50:28 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"
#include "Utils.hpp"

bool
IRC::is_valid_nick(std::string const &nickname){
	return ft::all_of(nickname.begin(), nickname.end(), is_valid_nick_char);
}

bool
IRC::is_valid_nick_char(char c){
	return isalnum(c) || is_special_char(c);
}

bool
IRC::is_special_char(char c){
	return c == '-'
	|| c == '['
	|| c == ']'
	|| c == '\\'
	|| c == '`'
	|| c == '^'
	|| c == '{'
	|| c == '}';
}
