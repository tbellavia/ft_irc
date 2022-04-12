/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:26:24 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/11 22:05:01 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include "User.hpp"

namespace IRC
{
	class Channel {
		std::string					m_name;
		std::set<IRC::User&>		m_subscribers;
	public:
		Channel(std::string const &name) 
			: m_name(name), m_subscribers() { }

		Channel(Channel const &other) 
			: m_name(other.m_name), m_subscribers(other.m_subscribers) { }

		Channel &operator=(Channel const &other) {
			if ( this == &other )
				return *this;
			m_name = other.m_name;
			m_subscribers = other.m_subscribers;
			return *this;
		}

		~Channel() { }

		void subscribe(User &user) {
			m_subscribers.insert(user);
		}

		void unsubscribe(User &user) {
			m_subscribers.erase(user);
		}

		void notify(std::string const &msg){
			
		}
	};
}


#endif
