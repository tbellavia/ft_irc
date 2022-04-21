/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPING.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:20:39 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/21 21:45:38 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPONG_HPP
#define CMDPONG_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdPING : public ACmd {
		CmdPING(CmdCtx &ctx, std::string const &request);
		virtual ~CmdPING();

		virtual void execute();
	};
}


#endif
