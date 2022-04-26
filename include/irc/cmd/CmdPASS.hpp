/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPASS.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:12 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/26 19:08:24 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPASS_HPP
#define CMDPASS_HPP

# include "ACmd.hpp"

namespace IRC
{
	/**
	 * 
	 * Command: PASS
	 * Parameters: <password>
	 * 
	 * The PASS command is used to set a 'connection password'.  Th
	 * password can and must be set before any attempt to register th
	 * connection is made.  Currently this requires that clients send a PAS
	 * command before sending the NICK/USER combination and servers *must
	 * send a PASS command before any SERVER command.  The password supplie
	 * must match the one contained in the C/N lines (for servers) or 
	 * lines (for clients).  It is possible to send multiple PASS command
	 * before registering but only the last one sent is used fo
	 * verification and it may not be changed once registered.  Numeric
	 * Replies:
	 * 		ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
	 * Example:
	 * 		PASS secretpasswordhere
	 * 
	 */
	struct CmdPASS : public ACmd {
		CmdPASS(CmdCtx &ctx, std::string const &request);
		virtual ~CmdPASS();

		virtual Actions execute();
	};
}

#endif
