/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPASS.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:12 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/20 23:02:48 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPASS_HPP
#define CMDPASS_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdPASS : public ACmd {
		CmdPASS(CmdCtx &ctx, std::string const &request);
		virtual ~CmdPASS();

		virtual void execute();
	};
}

#endif
