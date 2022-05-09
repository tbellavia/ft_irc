/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:34:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 12:42:32 by lperson-         ###   ########.fr       */
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
		Users		m_voices;
		Users		m_bans;
		Users		m_invites;
		Users		m_operators;

		User		*m_creator;
		std::string	m_name;
		std::string m_key;
		std::string m_topic;
		int			m_mode;
	public:
		Channel();
		Channel(std::string const &name, User *creator, int mode = CHAN_MODE_DEFAULT);
		Channel(Channel const &other);
		Channel &operator=(Channel const &other);
		~Channel();

		void set_name(std::string const &name);
		void set_mode(int mode);
		void set_key(std::string const &pass);
		void set_topic(std::string const &topic);

		bool is_banned(User *user) const;
		bool is_invited(User *user) const;
		bool is_operator(User *user) const;
		bool is_voices(User *user) const;

		std::string const &get_name() const;
		int get_mode() const;
		std::string const &get_key() const;
		std::string const &get_topic() const;

		Users::view_type get_users();

		bool equal_key(std::string const &key) const;

		bool is_default() const;
		bool is_private() const;
		bool is_secret() const;
		bool is_invite() const;
		bool is_moderated() const;

		void subscribe(User *user);
		void unsubscribe(User *user);
		Action notify(std::string const &msg);

		static bool is_channel_name(std::string const &name);
		static bool is_valid_name(std::string const &name);
	};
}


#endif
