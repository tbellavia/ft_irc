/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Masks.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:53:27 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/13 10:08:18 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASKS_HPP
# define MASKS_HPP

# include <string>
# include "Utils.hpp"

# define MASK_SYM_HOST			'#'
# define MASK_SYM_SERVER		'$'
# define MASK_SYM_SELECTOR_ALL	'*'
# define MASK_SYM_SELECTOR_OPT	'?'
# define IS_MASK_SELECTOR(c) \
	(c == MASK_SYM_SELECTOR_ALL || c == MASK_SYM_SELECTOR_OPT)
# define MASK_USER_SEPARATOR	"!@."

namespace IRC
{
	namespace mask
	{
		enum user_separator {
			NICKNAME_SEP = 1UL << 0x0UL,
			NETWORK_SEP = 1UL << 0x01UL,
			NAMESPACE_SEP = 1UL << 0x02UL
		};

		bool is_valid(std::string const &mask);
		bool match(std::string const &s, std::string const &mask);
		
		bool is_mask(std::string const &mask);
		bool is_server_mask(std::string const &mask);
		bool is_host_mask(std::string const &mask);
		bool is_server_or_host_mask(std::string const &mask);
		std::string construct_mask(std::string const &mask);
	}
}


#endif
