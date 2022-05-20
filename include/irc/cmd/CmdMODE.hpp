/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:54:08 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/20 14:16:25 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_HPP

# define CMD_MODE_HPP

# include "irc/ACmd.hpp"
# include "irc/cmd/CmdMODE/CmdMODEParse.hpp"

namespace IRC
{
	class CmdMODE : public ACmd
	{
	public:
		explicit CmdMODE(CmdCtx &ctx, std::string const &request);
		CmdMODE(CmdMODE const &copy);
		virtual ~CmdMODE();
	
		virtual Actions execute();

		CmdMODE &operator=(CmdMODE const &rhs);

	private:
		std::string					m_target;
		std::string					m_authorized_modes;
		CmdMODEParse				m_parser;
		std::string					m_mode_reply;
		std::vector<std::string>	m_mode_arguments_reply;

		// Channel modes utils
		Actions execute_channel_mode_(
			ReplyBuilder &reply
		);
		void execute_channel_mode_list_(
			Channel &channel,
			std::vector<Mode> const &mode_list,
			bool is_adding
		);

		// User mode utils
		Actions execute_user_mode_(ReplyBuilder &reply);
		void execute_user_mode_list_(
			User &user,
			std::vector<Mode> const &mode_list,
			bool is_adding
		);

	};
}

#endif
