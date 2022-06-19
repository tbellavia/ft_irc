/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:16 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/19 23:12:07 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP

# include "NumericReplies.hpp"
# include "User.hpp"
# include "Channel.hpp"

# include "Config.hpp"
# include "Actions.hpp"

# define TO_CHAR(n) ('0' + (n % 10))

namespace IRC
{
	class ReplyBuilder {
		std::string m_sender;
		User		*m_target;

		std::string build_header_(int code);
		std::string build_header_();
		std::string code_to_string_(int code);
		std::string get_user_mode_symbol_(User *user, Channel *channel = NULL);
	public:
		ReplyBuilder(std::string const &sender, User *target = NULL);
		ReplyBuilder(ReplyBuilder const &other);
		ReplyBuilder &operator=(ReplyBuilder const &other);
		~ReplyBuilder();

		// General replies - errors
		std::string error_need_more_params(std::string const &command);
		std::string error_not_registered();
		std::string error_already_registered();
		std::string error_no_privileges();
		std::string error_summon_disabled();
		std::string error_users_disabled();
		std::string error_unknown_command(std::string const &name);

		// Connection replies
		std::string reply_welcome(std::string const &user_mask);
		std::string reply_your_host(
			std::string const &server_name, std::string const &version
		);
		std::string reply_created(std::string const &date);
		std::string reply_my_info(ConfigServer const &config);

		IRC::Actions connection_complete_replies(
			User *sender, ConfigServer const &config
		);

		// Ping - Pong
		std::string reply_ping(std::string const &names);
		std::string reply_pong(std::string const &names);
		std::string error_no_origin();

		// Invite
		std::string reply_invite(
			std::string const &nickname, std::string const &channel_name
		);
		std::string reply_inviting(
			std::string const &nickname, std::string const &channel_name
		);

		// Nickname
		std::string error_no_such_nick(std::string const &nickname);
		std::string error_no_nickname_given();
		std::string error_nickname_in_use(std::string const &nickname);
		std::string error_erroneus_nickname(std::string const &nickname);
		std::string error_nickname_collision(std::string const &nickname);

		// Kill
		std::string reply_cmd_kill(
			std::string const &nickname, std::string const &comment
		);

		// Channel errors
		std::string error_no_such_channel(std::string const &channel);
		std::string error_too_many_channels(std::string const &channel);
		std::string error_bad_channel_key(std::string const &channel);
		std::string error_banned_from_channel(std::string const &channel);
		std::string error_invite_only_channel(std::string const &channel);
		std::string error_channel_is_full(std::string const &channel);
		std::string error_user_on_channel(
			std::string const &nickname, std::string const &channel_name
		);
		std::string	error_not_on_channel(std::string const &channel_name);
		std::string error_chan_o_privs_needed(std::string const &channel_name);
		std::string error_unknown_mode(char mode);
		std::string error_key_set(std::string const &channel_name);
		std::string error_user_not_in_channel(
			std::string const &nickname, std::string const &channel_name
		);

		// Sending errors
		std::string error_no_recipient(std::string const &cmd);
		std::string error_cannot_send_to_chan(std::string const &channel);
		std::string error_wild_toplevel(std::string const &mask);
		std::string error_no_toplevel(std::string const &mask);
		std::string error_no_text_to_send();

		// Channel replies
		std::string reply_channel_mode_is(Channel const &channel);
		std::string reply_channel_mode(
			std::string const &channel_name,
			std::string const &modes,
			std::vector<std::string> const &mode_parameters
		);
		std::string reply_new_topic(
			User *user, std::string const &channel_name,
			std::string const &topic
		);
		std::string reply_topic(std::string const &channel, std::string const &topic);
		std::string reply_notopic(std::string const &channel);
		std::string reply_name_reply(Channel &channel);
		std::string reply_end_of_names(std::string const &channel);
		std::string reply_join(std::string const &channel);
		std::string reply_ban_list(
			std::string const &channel_name, std::string const &banid
		);
		std::string reply_end_of_ban_list(std::string const &channel_name);

		std::string reply_who_reply(User *user, Channel *channel = NULL);
		std::string reply_end_of_who(Channel *channel = NULL);
		std::string reply_end_of_who(std::string const &mask);

		std::string reply_list_start();
		std::string reply_list(Channel const &channel);
		std::string reply_list_end();


		std::string reply_kick(
			User *sender,
			std::string const &channel_name,
			std::string const &user
		);
		std::string reply_kick(
			User *sender,
			std::string const &channel_name,
			std::string const &user,
			std::string const &comment
		);

		// User errors (mode etc...)
		std::string error_users_dont_match();
		std::string error_u_mode_unknown_flag();

		// User replies (infos etc...)
		std::string reply_u_mode_is(
			int user_mode
		);
		std::string reply_user_mode(
			std::string const &user_name, std::string const &modes
		);
		std::string reply_user_mode(
			std::string const &user_name, int user_mode
		);

		std::string reply_privmsg(std::string const &cmd, std::string const &msg, std::string const &channel);
		std::string reply_part(std::string const &channel, std::string const &message);
		std::string reply_quit(std::string const &message);

		std::string error_no_oper_host();
		std::string error_password_mismatch();
		std::string reply_youre_oper();

		// Whois
		std::string reply_whois_user(User *user);
		std::string reply_whois_channels(User *user, std::vector<Channel*> &channels);
		std::string reply_whois_operator(User *user);
		std::string reply_whois_server(User *user, std::string const &server_name, 
			std::string const &server_info);
		std::string reply_end_of_whois(std::string const &nick);
	};
}

#endif
