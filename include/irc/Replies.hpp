/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:16 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/10 11:19:05 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>
# include "NumericReplies.hpp"
# include "User.hpp"
# include "Channel.hpp"
# define TO_CHAR(n) ('0' + (n % 10))

namespace IRC
{
	class ReplyBuilder {
		std::string m_sender;
		User		*m_target;

		std::string build_header_(int code);
		std::string code_to_string_(int code);
	public:
		ReplyBuilder(std::string const &sender, User *target = NULL);
		ReplyBuilder(ReplyBuilder const &other);
		ReplyBuilder &operator=(ReplyBuilder const &other);
		~ReplyBuilder();

		std::string error_need_more_params(std::string const &command);
		std::string error_already_registered();
		
		// Nickname
		std::string error_no_nickname_given();
		std::string error_nickname_in_use(std::string const &nickname);
		std::string error_erroneus_nickname(std::string const &nickname);
		std::string error_nickname_collision(std::string const &nickname);

		// Channel errors
		std::string error_no_such_channel(std::string const &channel);
		std::string error_too_many_channels(std::string const &channel);
		std::string error_bad_channel_key(std::string const &channel);
		std::string error_banned_from_channel(std::string const &channel);
		std::string error_invite_only_channel(std::string const &channel);
		std::string error_channel_is_full(std::string const &channel);
		std::string	error_not_on_channel(std::string const &channel_name);
		std::string error_chan_o_privs_needed(std::string const &channel_name);

		// Channel replies
		std::string reply_topic(std::string const &channel, std::string const &topic);
		std::string reply_name_reply(Channel &channel);
		std::string reply_end_of_names(std::string const &channel);
		std::string reply_join(std::string const &channel);

		//User errors (mode etc...)
		std::string error_users_dont_match();

		std::string error_no_oper_host();
		std::string error_password_mismatch();
		std::string reply_youre_oper();

	};
}

#endif
