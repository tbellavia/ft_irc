/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKILL.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:20:11 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/15 09:25:57 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_KILL_HPP

# define CMD_KILL_HPP

# include "ACmd.hpp"

namespace IRC
{
	class CmdKILL : public ACmd
	{
	public:
		CmdKILL(CmdCtx &ctx, std::string const &request);
		CmdKILL(CmdKILL const &copy);
		~CmdKILL();

		Actions execute();

		CmdKILL &operator=(CmdKILL const &rhs);
	};
}

#endif
