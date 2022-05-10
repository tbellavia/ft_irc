/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:03:00 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/06 18:21:02 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_HPP
#define ACTION_HPP

# include <string>
# include <vector>
# include "Socket.hpp"
# include "User.hpp"

namespace IRC
{
	namespace Event
	{
		enum Event {
			SEND,
			DISCONNECT,
			BAN,
			IDLE
		};
	}
	
	class Action {
	public:
		Action();
		Action(int event);
		Action(int event, User *user, std::string const &response = std::string());
		Action(int event, std::vector<User*> users, std::string const &response = std::string());
		Action(Action const &other);
		Action &operator=(Action const &other);
		~Action();

		bool					isset(int event) const;
		int						event() const;
		std::vector<Socket*>	sockets() const;
		std::string const&		response() const;

		void add(User *user);

		static Action idle();
		static Action send(User *user, std::string const &response);
		static Action sendall(std::vector<User*> users, std::string const &response);
		static Action ban(User *user);
		static Action banall(std::vector<User*> users);
		static Action disconnect(User *user);
		static Action disconnectall(std::vector<User*> users);
	private:
		int						m_event;
		std::vector<Socket*>	m_sockets;
		std::string				m_response;
	};
}


#endif
