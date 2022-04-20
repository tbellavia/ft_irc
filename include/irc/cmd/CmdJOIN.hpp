/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJOIN.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:12 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/20 15:17:54 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDJOIN_HPP
#define CMDJOIN_HPP

# include "ACmd.hpp"

namespace IRC
{
	struct CmdJOIN : public ACmd {
		CmdJOIN();
		~CmdJOIN();

		virtual void execute();
	};
}


#endif
