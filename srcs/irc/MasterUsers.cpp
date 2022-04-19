/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterUsers.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:59:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 18:40:30 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MasterUsers.hpp"

IRC::MasterUsers::MasterUsers() :
    m_users() { }

IRC::MasterUsers::~MasterUsers() {
    std::map<int, User*>::iterator it;

    for ( it = m_users.begin() ; it != m_users.end() ; ++it ) {
        delete it->second;
    }
}

/**
 * Create
 * 
 * Create a user with a key set to the socket fd.
 */
IRC::User*
IRC::MasterUsers::create(Socket *socket) {
    if ( socket != NULL ){
        int key = socket->fd();
        User *user;

        user = new User(socket);
        m_users.insert(std::make_pair(key, user));
        return user;
    }
    return NULL;
}

/**
 * Remove
 * 
 * Remove the the user associated with the socket passed in parameter.
 */
void
IRC::MasterUsers::remove(Socket *socket) {
    if ( socket != NULL ){ 
        std::map<int, User*>::iterator found = m_users.find(socket->fd());

        if ( found != m_users.end() ) {
            delete found->second;
            m_users.erase(found);
        }
    }
}

/**
 * Find
 * 
 * Find a user by its socket.
 */
IRC::User*
IRC::MasterUsers::find(Socket *socket) {
    if ( socket != NULL ){
        std::map<int, User*>::iterator found = m_users.find(socket->fd());

        if ( found != m_users.end() )
            return found->second;
    }
    return NULL;
}