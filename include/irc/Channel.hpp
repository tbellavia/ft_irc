/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:26:24 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:40:59 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include "User.hpp"

namespace IRC
{
	enum Role {
		REGULAR,
		OPERATOR,
		ADMIN
	};

	class Channel {
		std::string					m_name;
		std::set<IRC::User*>		m_subscribers;
	public:
		Channel(std::string const &name);
		Channel(Channel const &other);
		Channel &operator=(Channel const &other);
		~Channel();

		void subscribe(User *user);
		void unsubscribe(User *user);
		void notify(std::string const &msg);
	};
}


#endif
