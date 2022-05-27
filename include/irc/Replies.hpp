/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:16 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/27 15:02:52 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP

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
		std::string get_user_mode_symbol_(Channel *channel, User *user);
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
		std::string error_unknown_mode(char mode);

		// Sending errors
		std::string error_no_recipient(std::string const &cmd);
		std::string error_cannot_send_to_chan(std::string const &channel);

		// Channel replies
		std::string reply_channel_mode_is(Channel const &channel);
		std::string reply_channel_mode_is(
			std::string const &channel_name,
			std::string const &modes,
			std::vector<std::string> const &mode_parameters
		);
		std::string reply_topic(std::string const &channel, std::string const &topic);
		std::string reply_name_reply(Channel &channel);
		std::string reply_end_of_names(std::string const &channel);
		std::string reply_join(std::string const &channel);
		std::string reply_channel_mode_is(
			Channel &channel
		);

		std::string reply_who_reply(Channel *channel, User *user);
		std::string reply_end_of_who(std::string const &name);

		// User errors (mode etc...)
		std::string error_users_dont_match();
		std::string error_u_mode_unknown_flag();

		// User replies (infos etc...)
		std::string reply_u_mode_is(
			std::string const &user_name, int user_mode
		);
		std::string reply_u_mode_is(
			std::string const &user_name, std::string const &modes
		);

		std::string reply_privmsg(std::string const &msg, std::string const &channel);

		std::string error_no_oper_host();
		std::string error_password_mismatch();
		std::string reply_youre_oper();

	};
}

#endif
