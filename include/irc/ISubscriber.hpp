/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISubscriber.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:25:40 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 12:57:49 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ISUBSCRIBER_HPP
#define FT_ISUBSCRIBER_HPP

# include <string>

namespace IRC
{
    struct ISubscriber {
        virtual void update(std::string const &msg) = 0;
        virtual ~ISubscriber();
    };
}

#endif
