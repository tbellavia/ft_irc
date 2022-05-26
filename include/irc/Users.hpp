/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:22:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/26 16:27:18 by bbellavi         ###   ########.fr       */
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
		typedef std::set<User*>::iterator					iterator;
		typedef std::set<User*>::const_iterator				const_iterator;
		typedef std::set<User*>::reverse_iterator			reverse_iterator;
		typedef std::set<User*>::const_reverse_iterator		const_reverse_iterator;
		typedef std::pair<iterator, iterator>				view_type;
		typedef std::pair<const_iterator, const_iterator>
															const_view_type;
		typedef std::pair<reverse_iterator, reverse_iterator>
															reverse_view_type;
		typedef std::pair<const_reverse_iterator, const_reverse_iterator>
															const_reverse_view_type;
		
		Users();
		Users(Users const &other);
		Users &operator=(Users const &other);
		~Users();

		void add(User *user);
		void remove(User *user);
		bool has(User *user) const;

		/**
		 * Getters and iterators for user.
		 */

		iterator find(User *to_find);
		const_iterator find(User *to_find) const;

		view_type				get_view();
		const_view_type			get_view() const;
		reverse_view_type		get_rview();
		const_reverse_view_type	get_rview() const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

		template<typename Pred>
		bool contains(Pred pred) const;

		template<typename Pred>
		std::vector<User*> select(Pred pred);

		Action notify(std::string const &msg, User *except = NULL);
	};

	template<typename Pred>
	bool Users::contains(Pred pred) const {
		iterator it;

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
		iterator it;
		
		for ( it = m_users.begin() ; it != m_users.end() ; ++it ){
			User *user = *it;

			if ( pred(user) )
				selected.push_back(user);
		}
		return selected;
	}
}


#endif
