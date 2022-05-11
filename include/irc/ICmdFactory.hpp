/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICmdFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:26:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 09:46:23 by lperson-         ###   ########.fr       */
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
		virtual ACmd *create_cmd(CmdCtx &ctx, std::string const &request) = 0;
		virtual ~ICmdFactory();

		ICmdFactory &operator=(ICmdFactory const &rhs);
	};
}


#endif
