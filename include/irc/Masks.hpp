/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Masks.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:53:27 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/28 20:11:15 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASKS_HPP
# define MASKS_HPP

# include <string>

# define MASK_SYM_HOST '#'
# define MASK_SYM_SERVER '$'
# define MASK_SYM_SELECTOR_ALL '*'
# define MASK_SYM_SELECTOR_OPT '?'
# define IS_MASK_SELECTOR(c) \
	(c == MASK_SYM_SELECTOR_ALL || c == MASK_SYM_SELECTOR_OPT)

namespace IRC
{
	namespace mask
	{
		bool is_valid(std::string const &mask);
		bool match(std::string const &s, std::string const &mask);
		
		bool is_server_mask(std::string const &mask);
		bool is_host_mask(std::string const &mask);
		bool is_server_or_host_mask(std::string const &mask);
	}
}


#endif
