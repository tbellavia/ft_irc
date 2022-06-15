/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:44 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/15 10:53:01 by lperson-         ###   ########.fr       */
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
# include <ostream>

namespace ft {
	bool						ends_with(std::string const &val, std::string const &ending);
	std::vector<std::string>	split(std::string const &s, std::string const &delim = " ");
	std::vector<std::string>	split_one(std::string const &s, std::string const &delim = " ");
	std::string					popfirst(std::string const &s);
	std::string					poplast(std::string const &s);
	void						remove(std::vector<std::string> &v, std::string const &val);
	std::string					string_toupper(std::string const &string);
	std::string					string_tolower(std::string const &string);

	template<typename InputIt>
	void debug_log_args(InputIt first, InputIt last, std::ostream &os){
		os << "(";
		for ( ; first != last ; ++first ){
			os << "'" << *first << "'";
			if ( (first + 1) != last )
				os << ",";
		}
		os << ")";
	}

	template<typename InputIt, typename UnaryPred>
	bool all_of(InputIt first, InputIt last, UnaryPred pred){
		for ( ; first != last ; ++first ){
			if ( !pred(*first) )
				return false;
		}
		return true;
	}

	template<typename InputIt, typename UnaryPred>
	bool any_of(InputIt first, InputIt last, UnaryPred pred){
		for ( ; first != last ; ++first ){
			if ( pred(*first) )
				return true;
		}
		return false;
	}

	void debug_notice(std::string const &msg);

}


#endif
