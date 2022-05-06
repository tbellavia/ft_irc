/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:34:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 00:48:15 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "Users.hpp"
# include "Parse.hpp"

# define CHAN_IDENTIFIERS "#&"
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
		Channel(std::string const &name, std::string const &pass, 
			std::string const &topic = "", int mode = CHAN_MODE_DEFAULT);
		Channel(Channel const &other);
		Channel &operator=(Channel const &other);
		~Channel();


		void set_name(std::string const &name);
		void set_role(int mode);
		void set_pass(std::string const &pass);
		void set_topic(std::string const &topic);

		std::string const &get_name() const;
		int get_mode() const;
		std::string const &get_pass() const;
		std::string const &get_topic() const;

		bool subscribe(User *user, std::string const &pass = "");
		void unsubscribe(User *user);
		Action notify(std::string const &msg);

		static bool is_channel(std::string const &name);
		static bool is_valid(std::string const &name);
	};
}


#endif
