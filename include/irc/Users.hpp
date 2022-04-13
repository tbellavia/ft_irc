/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 00:28:59 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/14 00:34:00 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
#define USERS_HPP

# include <map>
# include "User.hpp"

namespace IRC
{
	class Users {
			std::map<std::string, User*> m_users;
		public:
			Users();
			Users(Users const &other);
			Users &operator=(Users const &other);
			~Users();

			void add(User *user);
			void remove(User *user);
			bool contains(User *user) const;
			bool contains(std::string const &pseudo) const;
			void notify(std::string const &msg) const;
	};
}


#endif
