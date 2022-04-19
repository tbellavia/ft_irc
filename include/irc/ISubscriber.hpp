/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISubscriber.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:25:40 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 14:26:39 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ISUBSCRIBER_HPP
#define FT_ISUBSCRIBER_HPP

# include <string>

namespace IRC
{
    struct ISubscriber {
        virtual void update(std::string const &msg) = 0;
    };
}


#endif
