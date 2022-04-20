/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICmdFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:26:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/20 14:45:44 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICMDFACTORY_HPP
#define ICMDFACTORY_HPP

# include "CmdCtx.hpp"
# include "ACmd.hpp"

namespace IRC
{
	struct ICmdFactory {
		virtual ACmd *create_cmd(CmdCtx &ctx, std::string const &request) = 0;
	};
}


#endif
