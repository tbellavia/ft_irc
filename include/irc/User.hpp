/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:14:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:47:43 by bbellavi         ###   ########.fr       */
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
			User(Socket *socket, std::string const &pseudo = std::string(), int role = 0);
			User(User const &other);
			User &operator=(User const &other);
			virtual ~User();

			virtual void		update(std::string const &msg);
			
			std::string const	&get_pseudo() const;
			void				set_pseudo(std::string const &pseudo);
	};
}


#endif
