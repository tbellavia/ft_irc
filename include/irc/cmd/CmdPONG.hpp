/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPONG.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:20:39 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 15:25:01 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPONG_HPP
#define CMDPONG_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdPONG : public ACmd {
		CmdPONG(CmdCtx &ctx, std::string const &request);
		virtual ~CmdPONG();

		virtual void execute();
	};
}


#endif
