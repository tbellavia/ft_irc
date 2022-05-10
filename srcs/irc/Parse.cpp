/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:19:24 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/06 23:55:07 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"
#include "Utils.hpp"

bool
IRC::is_valid_nick(std::string const &nickname){
	return ft::all_of(nickname.begin(), nickname.end(), is_valid_nick_char);
}

bool
IRC::is_valid_user(std::string const &username){
	return ft::all_of(username.begin(), username.end(), is_nonwhite_char);
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

bool
IRC::is_nonwhite_char(char c){
	return !(c == 0x20 || c == 0x0 || c == 0xd || c == 0xa);
}

bool
IRC::is_ch(char c){
	return !(
		c == ' ' 
		|| c == 0x07 
		|| c == '\0' 
		|| c == '\n' 
		|| c == '\r' 
		|| c == ','
	);
}

bool
IRC::is_chstring(std::string const &chstring){
	return ft::all_of(chstring.begin(), chstring.end(), is_ch);
}