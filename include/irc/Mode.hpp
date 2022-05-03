/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:24:52 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/02 20:38:56 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
#define MODE_HPP

namespace IRC
{
	enum Mode {
		MODE_AWAY			= 0x01 << 0UL,
		MODE_INVISIBLE		= 0x01 << 1UL,
		MODE_WALLOPS		= 0x01 << 2UL,
		MODE_RESTRICTED		= 0x01 << 3UL,
		MODE_OPERATOR		= 0x01 << 4UL,
		MODE_LOCAL_OPERATOR = 0x01 << 5UL,
		MODE_RECEIPT		= 0x01 << 6UL,
		/* Special private Mode for connection verification */
		MODE_PASS_			= 0x01 << 7UL,
		MODE_NICK_			= 0x01 << 8UL,
		MODE_USER_			= 0x01 << 9UL
	};
}


#endif
