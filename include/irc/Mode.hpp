/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:06:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 15:44:14 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MODE_HPP
#define FT_MODE_HPP

namespace IRC
{
	enum Mode {
		MODE_ONBOARD	= 0x01 << 0UL,
		MODE_REGULAR	= 0x01 << 1UL,
		MODE_OPERATOR	= 0x01 << 2UL,
		MODE_ADMIN		= 0x01 << 3UL
	};
}




#endif
