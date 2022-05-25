/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actions.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:35:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/24 13:21:11 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

# include <queue>
# include "Action.hpp"

namespace IRC
{
	class Actions {
		std::queue<Action> m_actions;
		
	public:
		Actions();
		Actions(Action unique);
		Actions(Actions const &other);
		Actions &operator=(Actions const &other);
		~Actions();

		Actions &push(Action action);
		Actions &append(Actions &actions);
		Action pop();
		bool empty() const;
		
		static Actions unique_idle();
		static Actions unique_send(User *user, std::string const &response);
		static Actions unique_sendall(std::vector<User*> users, std::string const &response);
		static Actions unique_ban(User *user);
		static Actions unique_banall(std::vector<User*> users);
		static Actions unique_disconnect(User *user);
		static Actions unique_disconnectall(std::vector<User*> users);
	};
}


#endif
