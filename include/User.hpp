/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:14:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/12 02:59:09 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "Socket.hpp"

namespace IRC
{
	enum Role {
		REGULAR,
		OPERATOR,
		ADMIN
	};

	struct ISubscriber {
		virtual void update(std::string const &msg) = 0;
	};

	class User : public ISubscriber {
		Socket		*m_socket;
		std::string m_pseudo;
		Role		m_role;
	public:
		User(Socket *socket, std::string const &pseudo, Role role)
			: m_socket(socket), m_pseudo(pseudo), m_role(role) { }
		
		User(User const &other)
			: m_socket(other.m_socket), m_pseudo(other.m_pseudo), m_role(other.m_role) { }

		User &operator=(User const &other) {
			if ( &other == this )
				return *this;
			m_socket = other.m_socket;
			m_pseudo = other.m_pseudo;
			m_role = other.m_role;
			return *this;
		}

		~User() { }

		virtual void update(std::string const &msg) {
			m_socket->send(msg);
		}

		std::string const &get_pseudo() const {
			return m_pseudo;
		}
	};

	bool operator<(User &x, User &y) {
		return x.get_pseudo() < y.get_pseudo();
	}
}



#endif
