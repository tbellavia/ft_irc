/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:22:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/22 23:21:40 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDFACTORY_HPP
#define CMDFACTORY_HPP

# include <map>
# include "Utils.hpp"
# include "ICmdFactory.hpp"

# include "cmd/CmdPASS.hpp"
# include "cmd/CmdPONG.hpp"
# include "cmd/CmdNICK.hpp"

namespace IRC
{
	class CmdFactory : public ICmdFactory {
		typedef ACmd *(CmdFactory::*callback_t)(CmdCtx&, std::string const&);
		std::map<std::string, callback_t> m_callbacks;

		ACmd *create_pass_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_pong_cmd(CmdCtx &ctx, std::string const &request);
		ACmd *create_nick_cmd(CmdCtx &ctx, std::string const &request);
	public:
		CmdFactory();
		virtual ~CmdFactory();

		ACmd *create_cmd(CmdCtx &ctx, std::string const &request);
	};
}


#endif
