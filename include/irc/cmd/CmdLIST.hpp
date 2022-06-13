/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdLIST.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:10:27 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/13 14:38:30 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_HPP

# define CMD_LIST_HPP

# include "irc/ACmd.hpp"

namespace IRC
{
	class CmdLIST : public ACmd
	{
	public:
		CmdLIST(CmdCtx &ctx, std::string const &request);
		CmdLIST(CmdLIST const &copy);
		~CmdLIST();

		Actions execute();

		CmdLIST &operator=(CmdLIST const &rhs);
	};
}

#endif
