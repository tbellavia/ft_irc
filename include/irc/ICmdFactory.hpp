/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICmdFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:26:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/13 15:49:07 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICMDFACTORY_HPP
#define ICMDFACTORY_HPP

# include "CmdCtx.hpp"
# include "ACmd.hpp"

namespace IRC
{
	struct ICmdFactory {
		ICmdFactory();
		ICmdFactory(ICmdFactory const &copy);
		virtual ACmd *create_cmd(
			std::string const &name, CmdCtx &ctx, std::string const &request
		) = 0;
		virtual ~ICmdFactory();

		ICmdFactory &operator=(ICmdFactory const &rhs);
	};
}


#endif
