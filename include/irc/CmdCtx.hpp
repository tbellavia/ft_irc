/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdCtx.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:26:54 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/09 11:35:09 by lperson-         ###   ########.fr       */
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
		~CmdCtx();
		CmdCtx &operator=(CmdCtx const &other);
	};
}


#endif
