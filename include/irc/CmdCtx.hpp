/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdCtx.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:26:54 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 17:11:23 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDCTX_HPP
#define CMDCTX_HPP

# include "User.hpp"
# include "Channels.hpp"
# include "MasterUsers.hpp"

namespace IRC
{
	struct CmdCtx {
		User *sender;
		Channels &channels;
		MasterUsers &users;
		std::string &password;

		CmdCtx(User *sender, Channels &channels, MasterUsers &users, std::string &password);
		CmdCtx(CmdCtx const &other);
		CmdCtx &operator=(CmdCtx const &other);
	};
}


#endif
