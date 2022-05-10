/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:54:08 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/10 13:23:13 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_HPP

# define CMD_MODE_HPP

# include "irc/ACmd.hpp"

namespace IRC {
	class CmdMODE : public ACmd {
	public:
		CmdMODE(CmdCtx &ctx, std::string const &request);
		virtual ~CmdMODE();
	
		virtual Actions execute();

	private:
		Actions execute_channel_mode_(
			std::vector<std::string> const &args, ReplyBuilder &reply
		);
		Actions execute_user_mode_(
			std::vector<std::string> const &args, ReplyBuilder &reply
		);

		std::vector<std::string> parse_mode_string_(
			std::string const &mode_string
		) const;
	};
}

#endif
