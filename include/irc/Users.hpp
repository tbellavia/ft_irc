/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:22:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 18:46:45 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_USERS_HPP
#define FT_USERS_HPP

# include <set>
# include "User.hpp"

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
    };
}


#endif
