/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:04:33 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:43:56 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
#define CHANNELS_HPP

# include <map>
# include "Channel.hpp"

namespace IRC
{
	class Channels {
		std::map<std::string, Channel*> m_channels;
	public:
		Channels();
		Channels(Channels const &other);
		Channels &operator=(Channels const &other);
		~Channels();

		void add(std::string const &name);
		void remove(std::string const &name);
	};
}



#endif
