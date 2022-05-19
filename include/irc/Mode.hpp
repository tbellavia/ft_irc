/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:24:52 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/19 11:18:52 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

# define IRC_USER_MODE_STRING		"iswo"
# define IRC_USER_MODE_LEN			sizeof(IRC_USER_MODE_STRING)
# define IRC_CHANNEL_MODE_STRING	"opsitnmlbvk"
# define IRC_CHANNEL_MODE_LEN		sizeof(IRC_CHANNEL_MODE_STRING)

namespace IRC
{
	enum Mode {
		MODE_INVISIBLE		= 0x01 << 0UL, // 'i'
		MODE_SERVER_NOTICE	= 0x01 << 1UL, // 's'
		MODE_WALLOPS		= 0x01 << 2UL, // 'w'
		MODE_OPERATOR		= 0x01 << 3UL, // 'o'
		/* Special private Mode for connection verification */
		MODE_PASS_			= 0x01 << 4UL,
		MODE_NICK_			= 0x01 << 5UL,
		MODE_USER_			= 0x01 << 6UL
	};

	enum ChannelMode {
		CHAN_MODE_OPERATOR				= 0x01 << 0UL, // 'o'
		CHAN_MODE_PRIVATE				= 0x01 << 1UL, // 'p'
		CHAN_MODE_SECRET				= 0x01 << 2UL, // 's'
		CHAN_MODE_INVITE				= 0x01 << 3UL, // 'i'
		CHAN_MODE_TOPIC_BY_OP			= 0x01 << 4UL, // 't'
		CHAN_MODE_NO_OUTSIDE_MESSAGE	= 0x01 << 5UL, // 'n'
		CHAN_MODE_MODERATED				= 0x01 << 6UL, // 'm'
		CHAN_MODE_USER_LIMIT			= 0x01 << 7UL, // 'l'
		CHAN_MODE_BAN_MASK				= 0x01 << 8UL, // 'b
		CHAN_MODE_VOICE_USER			= 0x01 << 9UL, // 'v'
		CHAN_MODE_KEY					= 0x01 << 10UL // 'k'
	};
}


#endif
