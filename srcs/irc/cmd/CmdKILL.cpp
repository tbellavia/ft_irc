/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKILL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:22:18 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/15 10:03:50 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc/cmd/CmdKILL.hpp"

IRC::CmdKILL::CmdKILL(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "KILL")
{
}

IRC::CmdKILL::CmdKILL(CmdKILL const &copy):
		ACmd(copy)
{
}

IRC::CmdKILL::~CmdKILL()
{
}

IRC::Actions IRC::CmdKILL::execute()
{
	User *sender = this->sender();
	ReplyBuilder reply_error(this->server_name(), sender);

	if (m_arguments.size() < Expected_args(2))
		return Actions::unique_send(
			sender, reply_error.error_need_more_params(m_name)
		);

	if (!sender->is_server_operator())
		return Actions::unique_send(sender, reply_error.error_no_privileges());

	std::vector<User *>targets = m_ctx.users.select(
		User::NickSelector(m_arguments[1])
	);
	if (targets.empty())
		return Actions::unique_send(
			sender, reply_error.error_no_such_nick(m_arguments[1])
		);

	ReplyBuilder reply(sender->get_mask());
	return Actions::unique_sendall(
		targets, reply.reply_cmd_kill(m_arguments[1], m_arguments[2])
	);
}

IRC::CmdKILL &IRC::CmdKILL::operator=(CmdKILL const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
