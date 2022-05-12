/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:24:52 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/12 14:31:14 by lperson-         ###   ########.fr       */
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
		CHAN_MODE_OPERATOR		= 0x01 << 1UL, // 'o'
		CHAN_MODE_PRIVATE		= 0x01 << 2UL, // 'p'
		CHAN_MODE_SECRET		= 0x01 << 3UL, // 's'
		CHAN_MODE_INVITE		= 0x01 << 4UL, // 'i'
		CHAN_MODE_TOPIC_BY_OP	= 0x01 << 5UL, // 't'
		CHAN_MODE_MODERATED		= 0x01 << 6UL, // 'm'
		CHAN_MODE_USER_LIMIT	= 0x01 << 7UL  // 'l'
	};
}


#endif
