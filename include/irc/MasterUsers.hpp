/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterUsers.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 17:03:14 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MASTERUSERS_HPP
#define FT_MASTERUSERS_HPP

# include <map>
# include "User.hpp"

namespace IRC
{
    class MasterUsers {
        std::map<int, User*> m_users;
    public:
        MasterUsers();
        ~MasterUsers();
        
        User *create(Socket *socket);
    };
}


#endif
