/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Role.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:06:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/01 20:24:28 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ROLE_HPP
#define FT_ROLE_HPP

namespace IRC
{
	enum Role {
		ROLE_ONBOARD	= 0x01 << 0UL,
		ROLE_REGULAR	= 0x01 << 1UL,
		ROLE_OPERATOR	= 0x01 << 2UL,
		ROLE_ADMIN		= 0x01 << 3UL
	};
}




#endif
