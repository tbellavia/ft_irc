/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPRIVMSG.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:35:32 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/27 22:28:29 by bbellavi         ###   ########.fr       */
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
	private:
		void send_to_channel_(std::string const &name, std::string const &msg, Actions &actions, ReplyBuilder &reply);
		// void send_to_user_(std::string const &name, Actions &actions, ReplyBuilder &reply);
		// void send_to_user_mask_(std::string const &name, Actions &actions, ReplyBuilder &reply);
	};
}


#endif
