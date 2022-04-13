/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:04:33 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 00:32:55 by bbellavi         ###   ########.fr       */
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
		Channels() : m_channels() { }
		
		// Should implement deep copy
		Channels(Channels const &other) : m_channels(other.m_channels) { }

		Channels &operator=(Channels const &other) {
			if ( &other == this )
				return *this;
			m_channels = other.m_channels;
			return *this;
		}

		~Channels() {
			std::map<std::string, Channel*>::iterator it = m_channels.begin();

			for ( ; it != m_channels.end() ; ++it ){
				delete it->second;
			}
		}

		void add(std::string const &name) {
			m_channels.insert( std::make_pair(name, new Channel(name)) );
		}

		void remove(std::string const &name) {
			m_channels.erase( name );
		}
	};
}



#endif
