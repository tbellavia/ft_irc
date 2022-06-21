/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdINVITE.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:20:12 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/20 14:51:22 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdINVITE.hpp"

IRC::CmdINVITE::CmdINVITE(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "INVITE")
{
}

IRC::CmdINVITE::CmdINVITE(CmdINVITE const &copy):
		ACmd(copy)
{
}

IRC::CmdINVITE::~CmdINVITE()
{
}

IRC::Actions IRC::CmdINVITE::execute()
{
	ReplyBuilder server_reply(this->server_name(), this->sender());
	User *sender = this->sender();
	if (m_arguments.size() != Expected_args(2))
	{
		return Actions::unique_send(
			sender, server_reply.error_need_more_params(m_name)
		);
	}

	User *target = m_ctx.users.select_unique(
		User::NickSelector(m_arguments[1])
	);
	if (!target)
	{
		return Actions::unique_send(
			sender, server_reply.error_no_such_nick(m_arguments[1])
		);
	}

	Channel *channel = m_ctx.channels.find(m_arguments[2]);
	if (channel)
	{
		if (channel->find(this->sender()) == channel->end())
		{
			return Actions::unique_send(
				sender, server_reply.error_not_on_channel(m_arguments[2])
			);
		}

		if (
			channel->get_mode() & CHAN_MODE_INVITE &&
			!channel->is_operator_user(sender)
		)
		{
			return Actions::unique_send(
				sender, server_reply.error_chan_o_privs_needed(m_arguments[2])
			);
		}

		if (channel->find(target) != channel->end())
		{
			return Actions::unique_send(
				sender, server_reply.error_user_on_channel(
					m_arguments[1], m_arguments[2]
				)
			);
		}
	}
	ReplyBuilder user_reply(sender->get_mask());
	Actions actions;

	if (channel)
		channel->inviteUser(target);
	actions.push(
		IRC::Action(IRC::Event::SEND, target, user_reply.reply_invite(
			m_arguments[1], m_arguments[2]
		))
	);

	actions.push(
		IRC::Action(IRC::Event::SEND, sender, server_reply.reply_inviting(
			m_arguments[1], m_arguments[2]
		))
	);

	return actions;
}

IRC::CmdINVITE &IRC::CmdINVITE::operator=(CmdINVITE const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
