/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICmdFactory.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:52:53 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:25:05 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICmdFactory.hpp"

IRC::ICmdFactory::ICmdFactory() { }

IRC::ICmdFactory::ICmdFactory(ICmdFactory const &) { }

IRC::ICmdFactory::~ICmdFactory() { }

IRC::ICmdFactory &IRC::ICmdFactory::operator=(ICmdFactory const &) {
    return *this;
}