/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:22:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 15:46:30 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_USERS_HPP
#define FT_USERS_HPP

# include <map>
# include "User.hpp"

namespace IRC
{
    class Users {
        std::map<int, User> m_users;
    public:
        Users();
        Users(Users const &other);
        Users &operator=(Users const &other);
        ~Users();

        void add(User const &user);
        void remove(User const &user);
        User &search(int id);
    };
}


#endif
