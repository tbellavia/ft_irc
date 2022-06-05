/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTOPIC.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:00:40 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/05 23:01:49 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDTOPIC_HPP
#define CMDTOPIC_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdTOPIC : public ACmd {
		CmdTOPIC(CmdCtx &ctx, std::string const &request);
		virtual ~CmdTOPIC();

		virtual Actions execute();
	};
}


#endif
