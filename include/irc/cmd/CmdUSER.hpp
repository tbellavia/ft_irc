/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUSER.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:50:24 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/28 01:16:21 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDIUSER_HPP
#define CMDIUSER_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdUSER : public ACmd {
		CmdUSER(CmdCtx &ctx, std::string const &request);
		virtual ~CmdUSER();

		virtual Actions execute();
	};
}


#endif
