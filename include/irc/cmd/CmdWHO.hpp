/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdWHO.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:08:46 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/10 12:09:21 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDWHO_HPP
#define CMDWHO_HPP

namespace IRC
{
	struct CmdWHO : public ACmd {
		CdmWHO(CmdCtx &ctx, std::string const &request);
	}
}


#endif
