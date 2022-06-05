/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdQUIT.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:44:03 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/03 20:27:38 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDQUIT_HPP
#define CMDQUIT_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdQUIT : public ACmd {
		CmdQUIT(CmdCtx &ctx, std::string const &request);
		virtual ~CmdQUIT();

		virtual Actions execute();
	};
}


#endif
