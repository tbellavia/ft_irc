/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:34:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/31 12:43:58 by bbellavi         ###   ########.fr       */
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
		typedef	Users::iterator					iterator;
		typedef	Users::const_iterator			const_iterator;
		typedef	Users::reverse_iterator			reverse_iterator;
		typedef	Users::const_reverse_iterator	const_reverse_iterator;

		Channel();
		Channel(std::string const &name, User *creator, int mode = 0);
		Channel(Channel const &other);
		Channel &operator=(Channel const &other);
		~Channel();

		void set_name(std::string const &name);
		void set_mode(int mode);
		void unset_mode(int mode);
		void set_key(std::string const &pass);
		void set_topic(std::string const &topic);

		bool is_user(User *user) const;
		bool is_banned_user(User *user) const;
		bool is_invited_user(User *user) const;
		bool is_operator_user(User *user) const;
		bool is_voices_user(User *user) const;
		bool is_authorized(User *user) const;

		/**
		 * Getters for users:
		 * use iterators to iterate through users of the channel
		 *
		 * TODO: Maybe implements a way to iterate through each lists of users
		 * (banned, invited etc...). Need just one paramater for this.
		 */

		iterator find(User *to_find);
		const_iterator find(User *to_find) const;

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;


		Users::view_type get_users();

		std::string const &get_name() const;
		int get_mode() const;
		std::string const &get_key() const;
		std::string const &get_topic() const;

		bool equal_key(std::string const &key) const;

		bool is_private() const;
		bool is_secret() const;
		bool is_invite() const;
		bool is_moderated() const;
		bool is_outside_disable() const;

		void subscribe(User *user);
		void unsubscribe(User *user);
		void setOperator(User *user);
		void unsetOperator(User *user);
		void allowVoice(User *user);
		void disallowVoice(User *user);

		Action notify(std::string const &msg, User *sender = NULL);

		static bool is_channel_name(std::string const &name);
		static bool is_valid_name(std::string const &name);
	};
}


#endif
