/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKICK.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:46:17 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/09 13:50:46 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_KICK_HPP

# define CMD_KICK_HPP

# include "ACmd.hpp"

namespace IRC
{
	class CmdKICK : public ACmd
	{
	public:
		CmdKICK(CmdCtx &ctx, std::string const &request);
		CmdKICK(CmdKICK const &copy);
		~CmdKICK();

		Actions execute();

		CmdKICK &operator=(CmdKICK const &rhs);
	};
}

#endif
