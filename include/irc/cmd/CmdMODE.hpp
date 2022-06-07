/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:54:08 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/07 15:57:24 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_HPP

# define CMD_MODE_HPP

# include "irc/ACmd.hpp"

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
		typedef bool (CmdMODE::*setter_t)(
			bool, ReplyBuilder &, Actions &, Channel &, std::string const *
		);
		static setter_t const		m_parameters_func[
			IRC_CHANNEL_PARAMETERS_MODE_LEN
		];
		std::string					m_target;
		// Parsing
		std::string					m_authorized_modes;
		std::string					m_parameter_modes;
		std::vector<std::string>	m_mode_lists;
		std::vector<std::string>	m_mode_arguments;
		std::size_t					m_arg_cursor;
		// Reply
		std::string					m_mode_reply;
		std::vector<std::string>	m_mode_arguments_reply;

		// Channel modes utils
		Actions execute_channel_mode_(
			ReplyBuilder &reply
		);
		void execute_channel_mode_list_(
			Actions &actions,
			ReplyBuilder &reply,
			Channel &channel,
			std::string const &mode_list
		);
		bool set_channel_op_(
			bool to_add, ReplyBuilder &reply, Actions &actions,
			Channel &channel, std::string const *parameter
		);
		bool set_channel_limit_(
			bool to_add, ReplyBuilder &reply, Actions &actions,
			Channel &channel, std::string const *parameter
		);
		bool set_channel_ban_mask_(
			bool to_add, ReplyBuilder &reply, Actions &actions,
			Channel &channel, std::string const *parameter
		);
		bool set_channel_voice_user_(
			bool to_add, ReplyBuilder &reply, Actions &actions,
			Channel &channel, std::string const *parameter
		);

		// User mode utils
		Actions execute_user_mode_(ReplyBuilder &reply);
		void execute_user_mode_list_(
			Actions &actions,
			ReplyBuilder &reply,
			User &user,
			std::string const &mode_list
		);

		// Parsing
		Mode parse_one_mode_(char c);
		void parse_modes_(std::string const &mode_string);
		int char_to_mode_(char c);

	};
}

#endif
