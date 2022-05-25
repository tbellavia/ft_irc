/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:29:20 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/24 13:28:42 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Mode.hpp"

IRC::Mode::Mode():
		value(),
		litteral(),
		parameter()
{
}

IRC::Mode::Mode(int value, char litteral, std::string const *parameter):
		value(value),
		litteral(litteral),
		parameter(parameter)
{
}

IRC::Mode::Mode(Mode const &copy):
		value(copy.value),
		litteral(copy.litteral),
		parameter(new std::string(*copy.parameter))
{
}

IRC::Mode::~Mode()
{
	if (parameter)
		delete parameter;
}

IRC::Mode &IRC::Mode::operator=(Mode const &rhs)
{
	if (this == &rhs)
		return *this;

	value = rhs.value;
	litteral = rhs.litteral;
	parameter = new std::string(*rhs.parameter);
	return *this;
}
