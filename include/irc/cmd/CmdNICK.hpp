/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNICK.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:17:21 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 18:18:28 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDNICK_HPP
#define CMDNICK_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdNICK : public ACmd {
		CmdNICK(CmdCtx &ctx, std::string const &request);
		virtual ~CmdNICK();

		virtual void execute();
	};
}


#endif
