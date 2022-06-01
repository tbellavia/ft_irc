/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHO.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:08:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/31 17:56:47 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDWHO_HPP
#define CMDWHO_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdWHO : public ACmd {
		CmdWHO(CmdCtx &ctx, std::string const &request);
		virtual ~CmdWHO();

		virtual Actions execute();
	private:
		void drop_all_(Actions &actions, ReplyBuilder &reply);
		void drop_by_mask_(std::string const &mask, bool op_only, Actions &actions, ReplyBuilder &reply);
		void drop_by_channel_(std::string const &mask, bool op_only, Actions &actions, ReplyBuilder &reply);
	};
}


#endif
