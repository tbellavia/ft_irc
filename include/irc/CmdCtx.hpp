/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdCtx.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:26:54 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 02:15:59 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDCTX_HPP
#define CMDCTX_HPP

# include "User.hpp"
# include "Channels.hpp"
# include "MasterUsers.hpp"
# include "Config.hpp"

namespace IRC
{
	struct CmdCtx {
		User *sender;
		Channels &channels;
		MasterUsers &users;
		ConfigServer &config;

		CmdCtx();
		CmdCtx(User *sender, Channels &channels, MasterUsers &users, ConfigServer &config);
		CmdCtx(CmdCtx const &other);
		CmdCtx &operator=(CmdCtx const &other);
	};
}


#endif
