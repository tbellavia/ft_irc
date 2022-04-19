/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:06:18 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 14:56:50 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MODE_HPP
#define FT_MODE_HPP

namespace IRC
{
    enum Mode {
        MODE_REGULAR     = 0x01 << 0UL,
        MODE_OPERATOR    = 0x01 << 1UL,
        MODE_ADMIN       = 0x01 << 2UL
    };
}




#endif
