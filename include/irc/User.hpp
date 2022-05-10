/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:22:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/08 14:13:54 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

# include <string>
# include "Role.hpp"
# include "Mode.hpp"
# include "ISubscriber.hpp"
# include "Socket.hpp"

namespace IRC
{
	class User : public ISubscriber {
		std::string m_username;
		std::string m_nickname;
		std::string m_realname;
		int			m_mode;
		Socket		*m_socket;
	public:
		User();
		User(std::string const &pseudo, std::string const &nick, 
			std::string const &realname, int mode, Socket *socket);
		User(Socket *socket);
		User(User const &other);
		User &operator=(User const &other);
		virtual ~User();

		void set_username(std::string const &pseudo);
		void set_nickname(std::string const &nick);
		void set_realname(std::string const &realname);
		void set_mode(int mode);
		void set_socket(Socket *socket);

		/* State relatives member functions */
		void unset_mode(int mode);
		bool mode_isset(int mode) const;
		bool connected() const;
		bool connection_complete() const;
		bool pass_accepted() const;

		std::string const	&get_username() const;
		std::string const	&get_nickname() const;
		std::string const	&get_realname() const;
		std::string			get_hostname();
		int					get_mode() const;
		Socket				*get_socket();


		virtual void update(std::string const &msg);

		/**
		 * Pseudo predicate
		 * 
		 * Check if pseudo is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class PseudoSelector {
			std::string m_pseudo;
		public:
			PseudoSelector(std::string const &pseudo);
			bool operator()(User *user);
		};

		/**
		 * Nick predicate
		 * 
		 * Check if nickname is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class NickSelector {
			std::string m_nickname;
		public:
			NickSelector(std::string const &nickname);
			bool operator()(User *user);
		};

		/**
		 * Mode predicate
		 * 
		 * Check if mode is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class ModeSelector {
			int m_mode;
		public:
			ModeSelector(int mode);
			bool operator()(User *user);
		};

		/**
		 * Socket predicate
		 * 
		 * Check if socket is same than user passed in parameter.
		 * Functor to be passed to first class functions.
		 * 
		 * See Users::contains and Users::select.
		 */
		class SocketSelector {
			Socket *m_socket;
		public:
			SocketSelector(Socket *socket);
			bool operator()(User *user);
		};
	};
}


#endif
