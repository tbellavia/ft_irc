/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:29:20 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/08 18:32:45 by lperson-         ###   ########.fr       */
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
		parameter(NULL)
{
	if (copy.parameter)
		parameter = new std::string(*copy.parameter);
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
	if (parameter)
	{
		delete parameter;
		parameter = NULL;
	}
	if (rhs.parameter)
		parameter = new std::string(*rhs.parameter);
	return *this;
}
