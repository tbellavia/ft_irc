/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:43:00 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 15:46:39 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Users.hpp"

IRC::Users::Users() : m_users() { }

IRC::Users::Users(Users const &other) : m_users(other.m_users) { }

IRC::Users &IRC::Users::operator=(Users const &other) {
    if ( this == &other )
        return *this;
    m_users = other.m_users;
    return *this;
}

IRC::Users::~Users() { }

void
IRC::Users::add(User const &user) {
    
}

void
IRC::Users::remove(User const &user) {

}

IRC::User&
IRC::Users::search(int id) {
    
}