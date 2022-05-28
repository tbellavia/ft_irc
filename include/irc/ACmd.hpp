/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACmd.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:42:07 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/28 19:53:56 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACMD_HPP
#define ACMD_HPP

# include "CmdCtx.hpp"
# include "Action.hpp"
# include "Actions.hpp"
# include "Replies.hpp"
# include "Parse.hpp"
# include "CmdParser.hpp"

# define Expected_args(n) (n + 1)

namespace IRC
{
	class ACmd {
	protected:
		CmdCtx						&m_ctx;
		std::string					m_request;
		std::string					m_name;
		CmdParser					m_parser;
		std::vector<std::string>	m_arguments;

		ACmd(CmdCtx &ctx, std::string const &request, std::string const &name);
		ACmd(ACmd const &copy);

		virtual std::vector<std::string> parse();

		ACmd &operator=(ACmd const &rhs);

	public:
		virtual ~ACmd();

		virtual Actions execute() = 0;

		User		*sender();
		Channels	&channels();
		Users		&users();
		std::string	const &server_pass();
		std::string const &server_name();
	};
}


#endif
