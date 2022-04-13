/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:14:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 01:12:51 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "../network/Socket.hpp"

namespace IRC
{
	struct ISubscriber {
		virtual void update(std::string const &msg) = 0;
	};

	class User : public ISubscriber {
		Socket			*m_socket;
		std::string		m_pseudo;
		int				m_role;
	public:
		User(Socket *socket, std::string const &pseudo = std::string(), int role = 0)
			: m_socket(socket), m_pseudo(pseudo), m_role(role) {
				std::cout << "Create user" << std::endl;
			}
		
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

		virtual ~User() { }

		virtual void update(std::string const &msg) {
			m_socket->send(msg);
		}

		std::string const &get_pseudo() const {
			return m_pseudo;
		}

		void set_pseudo(std::string const &pseudo) {
			m_pseudo = pseudo;
		}
	};
}



#endif
