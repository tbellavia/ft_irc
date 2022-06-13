/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:22:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/13 15:44:18 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDFACTORY_HPP
#define CMDFACTORY_HPP

# include <map>
# include "Utils.hpp"
# include "ICmdFactory.hpp"

# include "cmd/CmdPASS.hpp"
# include "cmd/CmdNICK.hpp"
# include "cmd/CmdUSER.hpp"
# include "cmd/CmdOPER.hpp"
# include "cmd/CmdJOIN.hpp"
# include "cmd/CmdINVITE.hpp"
# include "cmd/CmdLIST.hpp"
# include "cmd/CmdKICK.hpp"
# include "cmd/CmdPRIVMSG.hpp"
# include "cmd/CmdWHO.hpp"
# include "cmd/CmdPING.hpp"
# include "cmd/CmdPONG.hpp"
# include "cmd/CmdQUIT.hpp"
# include "cmd/CmdMODE.hpp"
# include "cmd/CmdPART.hpp"
# include "cmd/CmdTOPIC.hpp"

namespace IRC
{
	class CmdFactory : public ICmdFactory {
		typedef ACmd *(CmdFactory::*callback_t)(CmdCtx&, std::string const&);
		std::map<std::string, callback_t>	m_callbacks;

		ACmd *create_pass_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_nick_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_user_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_oper_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_join_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_invite_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_list_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_kick_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_ping_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_pong_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_quit_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_who_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_mode_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_privmsg_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_part_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_topic_cmd(CmdCtx &ctx, std::string const &request);
	public:
		CmdFactory();
		CmdFactory(CmdFactory const &copy);
		virtual ~CmdFactory();

		ACmd *create_cmd(
			std::string const &name, CmdCtx &ctx, std::string const &request
		);

		CmdFactory &operator=(CmdFactory const &rhs);
	};
}


#endif
