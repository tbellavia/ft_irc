/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdOPER.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:13:48 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/05 15:34:55 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMDOPER_HPP
#define FT_CMDOPER_HPP

# include "ACmd.hpp"

namespace IRC {
	struct CmdOPER : ACmd {
		CmdOPER(CmdCtx &ctx, std::string const &request);
		virtual ~CmdOPER();

		virtual Actions execute();
	};
}

#endif
