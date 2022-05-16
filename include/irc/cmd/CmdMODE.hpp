/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODE.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:54:08 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/16 14:42:31 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_HPP

# define CMD_MODE_HPP

# include "irc/ACmd.hpp"
# include "irc/Channel.hpp"

namespace IRC {
	class CmdMODE : public ACmd {
	public:
		CmdMODE(CmdCtx &ctx, std::string const &request);
		virtual ~CmdMODE();
	
		virtual Actions execute();

	private:
		static int	m_modes[];
		static char	m_char_modes[];
		static int	m_channel_modes[];
		static char m_channel_char_modes[];

		// Channel modes utils
		Actions execute_channel_mode_(
			std::vector<std::string> const &args, ReplyBuilder &reply
		);
		int *char_to_channel_mode_(char c);
		int execute_channel_mode_list_(
			Actions &actions,
			ReplyBuilder &reply,
			Channel *target,
			std::pair<std::string, std::vector<std::string> > const &mode_list
		);

		// User mode utils
		Actions execute_user_mode_(
			std::vector<std::string> const &args, ReplyBuilder &reply
		);
		void add_mode_list_to_user_(
			User *target, std::string const &mode_list
		);
		void delete_mode_list_to_user_(
			User *target, std::string const &mode_list
		);
		int *char_to_mode_(char c);

		// Utils for chan and user modes
		char is_mode_string_valid_(
			std::string const &mode_string, std::string const &valid_modes
		);
		std::vector<std::string> parse_mode_string_(
			std::string const &mode_string
		) const;
		std::vector<
			std::pair<std::string, std::vector<std::string> >
		>
		parse_mode_arguments_(
			std::vector<std::string> const &mode_list,
			std::string const &mode_args,
			std::vector<std::string> const &arguments
		);

	};
}

#endif
