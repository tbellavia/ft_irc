/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:18:14 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 00:27:37 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>

namespace IRC
{
	bool is_valid_nick(std::string const &nickname);
	bool is_valid_nick_char(char c);
	bool is_special_char(char c);
}


#endif
