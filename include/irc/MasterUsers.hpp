/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterUsers.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 11:35:24 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MASTERUSERS_HPP
#define FT_MASTERUSERS_HPP

# include <map>
# include "User.hpp"

namespace IRC
{
	/**
	 * MasterUsers
	 * 
	 * 
	 * Create and manage user creation that will be passed to other objects
	 * as a procuration.
	 * MasterUsers manage the liftetime of a user, from the creation to
	 * the deletion.
	 * User objects will be passed as a reference to other objects.
	 */
	class MasterUsers {
		std::map<int, User*> m_users;
	public:
		MasterUsers();
		MasterUsers(MasterUsers const &copy);
		~MasterUsers();

		User *create(Socket *socket);
		void remove(Socket *socket);
		User *find(Socket *socket);

		template<typename Pred>
		bool contains(Pred pred);

		template<typename Pred>
		std::vector<User*> select(Pred pred);
	};

	template<typename Pred>
	bool MasterUsers::contains(Pred pred){
		std::map<int, User*>::iterator it;

		for ( it = m_users.begin() ; it != m_users.end() ; ++it ){
			User *user = it->second;

			if ( pred(user) ){
				return true;
			}
		}
		return false;
	}

	template<typename Pred>
	std::vector<User*> MasterUsers::select(Pred pred){
		std::vector<User*>			selected;
		std::map<int, User*>::iterator	it; 

		for ( it = m_users.begin() ; it != m_users.end() ; ++it ){
			User *user = it->second;

			if ( pred(user) )
				selected.push_back(user);
		}
		return selected;
	}
}


#endif
