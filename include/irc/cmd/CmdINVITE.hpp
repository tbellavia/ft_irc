/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdINVITE.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:17:57 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/08 16:19:57 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_INVITE_HPP

# define CMD_INVITE_HPP

# include "ACmd.hpp"

namespace IRC
{
	class CmdINVITE : public ACmd
	{
	public:
		CmdINVITE(CmdCtx &ctx, std::string const &request);
		CmdINVITE(CmdINVITE const &copy);
		~CmdINVITE();

		Actions execute();

		CmdINVITE &operator=(CmdINVITE const &rhs);
	};
}

#endif
