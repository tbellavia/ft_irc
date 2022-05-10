/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHO.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:08:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/10 12:19:29 by bbellavi         ###   ########.fr       */
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
	};
}


#endif
