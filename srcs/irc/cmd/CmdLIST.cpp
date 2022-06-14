/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdLIST.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:12:50 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/13 15:21:07 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdLIST.hpp"

IRC::CmdLIST::CmdLIST(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "LIST")
{
}

IRC::CmdLIST::CmdLIST(CmdLIST const &copy):
		ACmd(copy)
{
}

IRC::CmdLIST::~CmdLIST()
{
}

IRC::Actions IRC::CmdLIST::execute()
{
	std::vector<Channel> target_channels;

	if (m_arguments.size() >= Expected_args(1)) {
		std::vector<std::string> channel_names = ft::split(m_arguments[1], ",");
		for (std::size_t i = 0; i < channel_names.size(); ++i)
		{
			Channel *chan = m_ctx.channels.find(channel_names[i]);
			if (chan)
			{
				target_channels.push_back(*chan);
			}
		}
	}
	else
		target_channels = m_ctx.channels.get_channels();

	User *sender = this->sender();
	ReplyBuilder reply(this->server_name(), sender);
	Actions queue;
	for (std::size_t i = 0; i < target_channels.size(); ++i)
	{
		if (i == 0) {
			queue.push(Action::send(sender, reply.reply_list_start()));
		}
		queue.push(
			Action::send(sender, reply.reply_list(target_channels[i]))
		);
	}
	queue.push(IRC::Action::send(sender, reply.reply_list_end()));
	return queue;
}

IRC::CmdLIST &IRC::CmdLIST::operator=(CmdLIST const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
