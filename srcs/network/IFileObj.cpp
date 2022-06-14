/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IFileObj.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:00:07 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/14 19:13:31 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IFileObj.hpp"

IFileObj::~IFileObj()
{
}

bool operator==(IFileObj const &lhs, IFileObj const &rhs)
{
	return lhs.fd() == rhs.fd();
}

bool operator!=(IFileObj const &lhs, IFileObj const &rhs)
{
	return !(lhs == rhs);
}
