/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHOIS.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:56:33 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/19 22:53:47 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDWHOIS_HPP
#define CMDWHOIS_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdWHOIS : public ACmd {
		CmdWHOIS(CmdCtx &ctx, std::string const &request);
		~CmdWHOIS();

		virtual Actions execute();
	private:
		void single_whois(User *target, Actions &actions, ReplyBuilder &reply);
		void whois(std::string const &nickname, Actions &actions, ReplyBuilder &reply);
		void whois_mask(std::string const &nickmask, Actions &actions, ReplyBuilder &reply);
	};
}


#endif
