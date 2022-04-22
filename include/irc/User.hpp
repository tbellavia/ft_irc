/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:22:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 15:47:24 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_USER_HPP
#define FT_USER_HPP

# include <string>
# include "Mode.hpp"
# include "ISubscriber.hpp"
# include "Socket.hpp"

namespace IRC
{
	class User : public ISubscriber {
		std::string m_pseudo;
		std::string m_nickname;
		int			m_mode;
		Socket		*m_socket;
	public:
		User();
		User(std::string const &pseudo, std::string const &nick, 
			int mode, Socket *socket);
		User(Socket *socket);
		User(User const &other);
		User &operator=(User const &other);
		virtual ~User();

		void set_pseudo(std::string const &pseudo);
		void set_nick(std::string const &nick);
		void set_mode(int mode);
		void set_socket(Socket *socket);

		bool mode_isset(int mode);

		std::string const	&get_pseudo() const;
		std::string const	&get_nick() const;
		int					get_mode() const;
		Socket				*get_socket();


		virtual void update(std::string const &msg);
	};
}


#endif
