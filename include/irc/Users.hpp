/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:22:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/06 18:17:08 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_USERS_HPP
#define FT_USERS_HPP

# include <set>
# include "User.hpp"
# include "Action.hpp"
namespace IRC
{
	class Users {
		std::set<User*> m_users;
	public:
		Users();
		Users(Users const &other);
		Users &operator=(Users const &other);
		~Users();

		void add(User *user);
		void remove(User *user);
		bool has(User *user);

		template<typename Pred>
		bool contains(Pred pred);

		template<typename Pred>
		std::vector<User*> select(Pred pred);
		
		Action notify(std::string const &msg);
	};

	template<typename Pred>
	bool Users::contains(Pred pred){
		std::set<User*>::iterator it;

		for ( it = m_users.begin() ; it != m_users.end() ; ++it ){
			User *user = *it;

			if ( pred(user) ){
				return true;
			}
		}
		return false;
	}

	template<typename Pred>
	std::vector<User*> Users::select(Pred pred){
		std::vector<User*>			selected;
		std::set<User*>::iterator	it; 

		for ( it = m_users.begin() ; it != m_users.end() ; ++it ){
			User *user = *it;

			if ( pred(user) )
				selected.push_back(user);
		}
		return selected;
	}
}


#endif
