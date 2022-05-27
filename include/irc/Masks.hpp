/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Masks.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:53:27 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/27 22:01:10 by bbellavi         ###   ########.fr       */
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
	bool is_valid_mask(std::string const &mask);
}


#endif
