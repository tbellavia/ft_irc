/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPART.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:00:44 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/02 15:22:48 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPART_HPP
#define CMDPART_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdPART : public ACmd {
		CmdPART(CmdCtx &ctx, std::string const &request);
		virtual ~CmdPART();

		virtual Actions execute();
	};
}


#endif
