/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPING.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:41:35 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/08 13:55:21 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PING_HPP

# define CMD_PING_HPP

# include "ACmd.hpp"

namespace IRC
{
	class CmdPING : public ACmd
	{
	public:
		CmdPING(CmdCtx &ctx, std::string const &request);
		CmdPING(CmdPING const &copy);
		~CmdPING();

		Actions execute();

		CmdPING &operator=(CmdPING const &rhs);
	};
}

#endif
