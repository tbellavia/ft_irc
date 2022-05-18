/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:24:52 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/16 15:01:00 by lperson-         ###   ########.fr       */
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
		/* Special private Mode for connection verification */
		MODE_PASS_			= 0x01 << 6UL,
		MODE_NICK_			= 0x01 << 7UL,
		MODE_USER_			= 0x01 << 8UL
	};

	enum ChannelMode {
		CHAN_MODE_OPERATOR		= 0x01 << 0UL, // 'o'
		CHAN_MODE_PRIVATE		= 0x01 << 1UL, // 'p'
		CHAN_MODE_SECRET		= 0x01 << 2UL, // 's'
		CHAN_MODE_INVITE		= 0x01 << 3UL, // 'i'
		CHAN_MODE_TOPIC_BY_OP	= 0x01 << 4UL, // 't'
		CHAN_MODE_NO_OUTSIDE	= 0x01 << 5UL, // 'n'
		CHAN_MODE_MODERATED		= 0x01 << 6UL, // 'm'
		CHAN_MODE_USER_LIMIT	= 0x01 << 7UL, // 'l'
		CHAN_MODE_BAN_MASK		= 0x01 << 8UL, // 'b'
		CHAN_MODE_VOICE			= 0x01 << 9UL, // 'v'
		CHAN_MODE_KEY			= 0x01 << 10UL, // 'k'
	};
}


#endif
