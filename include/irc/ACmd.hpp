/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:42:07 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 23:07:43 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACMD_HPP
#define ACMD_HPP

# include "CmdCtx.hpp"
# include "Action.hpp"
# include "Actions.hpp"

namespace IRC
{
	class ACmd {
	protected:
		CmdCtx		&m_ctx;
		std::string m_request;
	public:
		ACmd(CmdCtx &ctx, std::string const &request);
		virtual ~ACmd();
		
		virtual Actions execute() = 0;
	};
}


#endif