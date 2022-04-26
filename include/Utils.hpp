/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:44 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/26 18:02:34 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tony on 29/03/2022.
//

#ifndef FT_IRC_UTILS_HPP
# define FT_IRC_UTILS_HPP

# include <string>
# include <algorithm>
# include <vector>

namespace ft {
	bool						ends_with(std::string const &val, std::string const &ending);
	std::vector<std::string>	split(std::string const &s, std::string const &delim = " ");
	std::vector<std::string>	split_one(std::string const &s, std::string const &delim = " ");
	std::string					popfirst(std::string const &s);
	std::string					poplast(std::string const &s);
	void						remove(std::vector<std::string> &v, std::string const &val = "");

	void						debug_notice(std::string const &msg);
}


#endif
