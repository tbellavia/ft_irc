/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPRIVMSG.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:35:32 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/26 15:36:44 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPRIVMSG_HPP
#define CMDPRIVMSG_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdPRIVMSG : public ACmd {
		CmdPRIVMSG(CmdCtx &ctx, std::string const &request);
		virtual ~CmdPRIVMSG();

		virtual Actions execute();
	};
}


#endif
