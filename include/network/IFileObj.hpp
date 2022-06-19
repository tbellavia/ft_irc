/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IFileObj.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:57:30 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/14 19:12:39 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_FILE_OBJ_HPP

# define I_FILE_OBJ_HPP

class IFileObj
{
public:
	virtual ~IFileObj();

	virtual int fd() const = 0;
	virtual void close() = 0;
};


bool operator==(IFileObj const &lhs, IFileObj const &rhs);
bool operator!=(IFileObj const &lhs, IFileObj const &rhs);

#endif
