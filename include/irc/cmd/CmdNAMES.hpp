/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNAMES.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 23:06:03 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/06 23:08:32 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDNAMES_HPP
#define CMDNAMES_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdNAMES : public ACmd {
		CmdNAMES(CmdCtx &ctx, std::string const &request);
		~CmdNAMES();

		virtual Actions execute();
	};
}


#endif
