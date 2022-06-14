/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKICK.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:42 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/09 15:43:54 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc/cmd/CmdKICK.hpp"

IRC::CmdKICK::CmdKICK(CmdCtx &ctx, std::string const &request):
		ACmd(ctx, request, "KICK")
{
}

IRC::CmdKICK::CmdKICK(CmdKICK const &copy):
		ACmd(copy)
{
}

IRC::CmdKICK::~CmdKICK()
{
}

IRC::Actions IRC::CmdKICK::execute()
{
	User *sender = this->sender();
	ReplyBuilder reply(this->server_name(), sender);

	if (m_arguments.size() < Expected_args(2))
		return Actions::unique_send(
			sender, reply.error_need_more_params(m_name)
		);

	std::vector<std::string> channel_list = ft::split(m_arguments[1], ",");
	std::vector<std::string> users_kicked = ft::split(m_arguments[2], ",");

	if (channel_list.size() != users_kicked.size() && channel_list.size() != 1)
		return Actions::unique_idle();

	Actions queue;
	for (std::size_t i = 0; i < channel_list.size(); ++i)
	{
		Channel *channel = m_ctx.channels.find(channel_list[0]);
		if (!channel)
		{
			queue.push(
				Action::send(
					sender, reply.error_no_such_channel(channel_list[i])
				)
			);
			continue;
		}
		if (!channel->is_user(sender))
		{
			queue.push(
				Action::send(
					sender, reply.error_not_on_channel(channel_list[i])
				)
			);
			continue;
		}
		if (!channel->is_operator_user(sender))
		{
			queue.push(
				Action::send(
					sender, reply.error_chan_o_privs_needed(channel_list[i])
				)
			);
			continue;
		}

		if (channel_list.size() == 1)
		{
			for (std::size_t f = 0; f < users_kicked.size(); ++f)
			{
				User *user = m_ctx.users.select_unique(
					User::NickSelector(users_kicked[f])
				);

				if (!user || !channel->is_user(user))
				{
					queue.push(
						Action::send(
							sender,
							reply.error_user_not_in_channel(
								users_kicked[i], channel->get_name()
							)
						)
					);
					continue;
				}

				if (m_arguments.size() == Expected_args(3))
				{
					queue.push(
						channel->notify(
							reply.reply_kick(
								sender, channel->get_name(),
								user->get_nickname(), m_arguments[3]
							)
						)
					);
				}
				else
				{
					queue.push(
						channel->notify(
							reply.reply_kick(
								sender, channel->get_name(),
								user->get_nickname()
							)
						)
					);
				}
				channel->unsubscribe(user);
			}
		}
		else
		{
			User *user = m_ctx.users.select_unique(
				User::NickSelector(users_kicked[i])
			);

			if (!user || !channel->is_user(user))
			{
				queue.push(
					Action::send(
						sender,
						reply.error_user_not_in_channel(
							users_kicked[i], channel->get_name()
						)
					)
				);
				continue;
			}

			if (m_arguments.size() == Expected_args(3))
			{
				queue.push(
					channel->notify(
						reply.reply_kick(
							sender, channel->get_name(),
							user->get_nickname(), m_arguments[3]
						)
					)
				);
			}
			else
			{
				queue.push(
					channel->notify(
						reply.reply_kick(
							sender, channel->get_name(),
							user->get_nickname()
						)
					)
				);
			}
			channel->unsubscribe(user);
		}
	}
	return queue;
}

IRC::CmdKICK &IRC::CmdKICK::operator=(IRC::CmdKICK const &rhs)
{
	if (this == &rhs)
		return *this;
	ACmd::operator=(rhs);
	return *this;
}
