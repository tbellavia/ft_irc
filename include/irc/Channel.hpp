/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:34:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/06 18:28:14 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "Users.hpp"

namespace IRC
{
	class Channel {
		Users		m_users;
		std::string	m_name;
		std::string m_pass;
		std::string m_topic;
		int			m_mode;
	public:
		Channel();
		Channel(std::string const &name, std::string const &pass, int mode);
		// Channel(std::string const &name, int mode);
		Channel(Channel const &other);
		Channel &operator=(Channel const &other);
		~Channel();


		void set_name(std::string const &name);
		void set_role(int mode);
		void set_pass(std::string const &pass);

		std::string const &get_name() const;
		int get_mode() const;
		std::string const &get_pass() const;

		void subscribe(User *user);
		void unsubscribe(User *user);
		void notify(std::string const &msg);
	};
}


#endif
