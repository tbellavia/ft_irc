/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/19 13:08:56 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replies.hpp"

IRC::ReplyBuilder::ReplyBuilder(std::string const &sender, User *target) :
	m_sender(sender), m_target(target) { }

IRC::ReplyBuilder::ReplyBuilder(ReplyBuilder const &other) : 
	m_sender(other.m_sender), m_target(other.m_target) {}

IRC::ReplyBuilder&
IRC::ReplyBuilder::operator=(ReplyBuilder const &other) {
	if ( &other == this )
		return *this;
	m_sender = other.m_sender;
	m_target = other.m_target;
	return *this;
}

IRC::ReplyBuilder::~ReplyBuilder() { }

std::string
IRC::ReplyBuilder::error_need_more_params(std::string const &command){
	std::string reply = this->build_header_(NumericReplies::ERR_NEEDMOREPARAMS);

	reply.append(" ");
	reply.append(command);
	reply.append(" :Not enough parameters");
	return reply;
}

std::string
IRC::ReplyBuilder::error_already_registered() {
	std::string reply = this->build_header_(NumericReplies::ERR_ALREADYREGISTRED);
	
	reply.append(" ");
	reply.append(":You may not reregister");
	return reply;
}

std::string IRC::ReplyBuilder::error_no_nickname_given(){
	std::string reply = this->build_header_(NumericReplies::ERR_NONICKNAMEGIVEN);

	reply.append(" :No nickname given");
	return reply;
}

std::string IRC::ReplyBuilder::error_nickname_in_use(std::string const &nickname){
	std::string reply = this->build_header_(NumericReplies::ERR_NICKNAMEINUSE);

	reply.append(" ");
	reply.append(nickname);
	reply.append(" :Nickname is already in use");
	return reply;
}

std::string IRC::ReplyBuilder::error_erroneus_nickname(std::string const &nickname){
	std::string reply = this->build_header_(NumericReplies::ERR_ERRONEUSNICKNAME);

	reply.append(" ");
	reply.append(nickname);
	reply.append(" :Erroneus nickname");
	return reply;
}

std::string IRC::ReplyBuilder::error_nickname_collision(std::string const &nickname){
	std::string reply = this->build_header_(NumericReplies::ERR_NICKCOLLISION);

	reply.append(" ");
	reply.append(nickname);
	reply.append(" :Nickname collision KILL");
	return reply;
}

std::string
IRC::ReplyBuilder::error_no_oper_host() {
	std::string reply = this->build_header_(NumericReplies::ERR_NOOPERHOST);

	reply.append(" :No O-lines for your host");
	return reply;
}

std::string
IRC::ReplyBuilder::error_password_mismatch() {
	std::string reply = this->build_header_(NumericReplies::ERR_PASSWDMISMATCH);

	reply.append(" :Password incorrect");
	return reply;
}

std::string
IRC::ReplyBuilder::reply_youre_oper() {
	std::string reply = this->build_header_(NumericReplies::RPL_YOUREOPER);

	reply.append(" :You are now an IRC operator");
	return reply;
}

std::string
IRC::ReplyBuilder::error_no_such_channel(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::ERR_NOSUCHCHANNEL);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :No such channel");
	return reply;
}

std::string
IRC::ReplyBuilder::error_too_many_channels(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::ERR_TOOMANYCHANNELS);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :You have joined too many channels");
	return reply;
}
std::string
IRC::ReplyBuilder::error_bad_channel_key(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::ERR_BADCHANNELKEY);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :Cannot join channel (+k)");
	return reply;
}
std::string
IRC::ReplyBuilder::error_banned_from_channel(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::ERR_BANNEDFROMCHAN);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :Cannot join channel (+b)");
	return reply;
}
std::string
IRC::ReplyBuilder::error_invite_only_channel(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::ERR_INVITEONLYCHAN);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :Cannot join channel (+i)");
	return reply;
}
std::string
IRC::ReplyBuilder::error_channel_is_full(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::ERR_CHANNELISFULL);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :Cannot join channel (+l)");
	return reply;
}

std::string
IRC::ReplyBuilder::error_not_on_channel(std::string const &channel_name) {
	std::string reply = this->build_header_(NumericReplies::ERR_NOTONCHANNEL);

	reply.append(" ");
	reply.append(channel_name);
	reply.append(" :You're not on that channel");
	return reply;
}

std::string
IRC::ReplyBuilder::error_chan_o_privs_needed(std::string const &channel_name) {
	std::string reply = this->build_header_(
		NumericReplies::ERR_CHANOPRIVSNEEDED
	);

	reply.append(" ");
	reply.append(channel_name);
	reply.append(" :You're not channel operator");
	return reply;
}

// User errors (mode etc...)
std::string
IRC::ReplyBuilder::error_users_dont_match() {
	std::string reply = this->build_header_(NumericReplies::ERR_USERSDONTMATCH);

	reply.append(" :Can't change mode for other users");
	return reply;
}

std::string
IRC::ReplyBuilder::error_u_mode_unknown_flag() {
	std::string reply = this->build_header_(
		NumericReplies::ERR_UMODEUNKNOWNFLAG
	);

	reply.append(" :Unknown MODE flag");
	return reply;
}

// User replies (infos etc...)
std::string
IRC::ReplyBuilder::reply_u_mode_is(
	std::string const &user_name, int user_mode
) {
	std::string reply = this->build_header_(NumericReplies::RPL_UMODEIS);

	reply.append(" ");
	reply.append(user_name);
	reply.append(" :+");

	std::string const mode_string = IRC_USER_MODE_STRING;
	for (std::string::size_type i = 0; i < mode_string.length(); ++i) {
		if ( user_mode & (0x01 << i) )
			reply.push_back(mode_string[i]);
	}
	return reply;
}

std::string
IRC::ReplyBuilder::reply_topic(std::string const &channel, std::string const &topic){
	std::string reply = this->build_header_(NumericReplies::RPL_TOPIC);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :");
	reply.append(topic);
	return reply;
}

std::string
IRC::ReplyBuilder::reply_name_reply(Channel &channel){
	std::string reply = this->build_header_(NumericReplies::RPL_NAMREPLY);
	Users::view_type users = channel.get_users();

	reply.append(" ");
	reply.append(channel.get_name());
	reply.append(" :");
	for ( bool is_first = true ; users.first != users.second ; ++users.first, is_first = false ){
		// `@` -> channel operator
		// `+` -> channel voices
		User *user = *users.first;

		if ( !is_first )
			reply.append(" ");
		// TODO: Do correct symbol assignation
		reply.append("@");
		// if ( channel.is_voices_user(user) || channel.is_operator_user(user) )
		// 	reply.append("@");
		// else
		// 	reply.append("+");
		reply.append(user->get_nickname());
	}
	return reply;
}

std::string
IRC::ReplyBuilder::reply_end_of_names(std::string const &channel){
	std::string reply = this->build_header_(NumericReplies::RPL_ENDOFNAMES);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :End of /NAMES list");
	return reply;
}

std::string
IRC::ReplyBuilder::reply_who_reply(Channel *channel, User *user) {
	std::string reply = this->build_header_(NumericReplies::RPL_WHOREPLY);

	// "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
	reply.append(" ");
	reply.append(channel->get_name());
	reply.append(" ");
	reply.append(user->get_username());
	reply.append(" ");
	reply.append(user->get_hostname());
	reply.append(" ");
	reply.append(m_sender);
	reply.append(" ");
	reply.append(user->get_nickname());
	reply.append(" ");
	/*
	if ( user->mode_isset(MODE_AWAY) )
		reply.append("G");
	else
	*/
		reply.append("H");
	if ( channel != NULL ){
		reply.append(get_user_mode_symbol_(channel, user));
	}
	reply.append(" ");
	// We don't manage server to server, the hopcount is always 0
	reply.append("0 :");
	reply.append(user->get_realname());
	return reply;
}

std::string
IRC::ReplyBuilder::reply_end_of_who(std::string const &name) {
	std::string reply = this->build_header_(NumericReplies::RPL_ENDOFWHO);

	reply.append(" ");
	reply.append(name);
	reply.append(" :End of /WHO list");
	return reply;
}

std::string
IRC::ReplyBuilder::build_header_(int code){
	std::string s;

	s.append(":");
	s.append(m_sender);
	s.append(" ");
	// TODO: Manage 0 padding.
	s.append(this->code_to_string_(code));
	s.append(" ");
	if ( m_target == NULL )
		s.append("*");
	else
		// TODO: For now, header is built with ip representation, should we use
		// the hostname ? 
		s.append(m_target->get_socket()->ip());
	return s;
}

std::string
IRC::ReplyBuilder::reply_join(std::string const &channel){
	// :<nick>!<user>@<host> JOIN <channel> * :realname
	std::string reply;

	reply 
		= ":" 
		+ m_target->get_nickname() 
		+ "!" 
		+ m_target->get_username() 
		+ "@" 
		+ m_target->get_socket()->hostname()
		+ " JOIN "
		+ channel
		+ " * :realname";
	return reply;
}

std::string
IRC::ReplyBuilder::code_to_string_(int digit){
	std::string a, b, c;

	a = TO_CHAR(digit);
	digit /= 10;
	b = TO_CHAR(digit);
	digit /= 10;
	c = TO_CHAR(digit);
	return c + b + a;
}

/**
 * Get user mode symbol
 * 
 * Returns `@' or `+' if user is a channel operator
 * or has been allowed to talk on the channel, the
 * symbol `@` is returned, otherwise the symbol
 * `+' is returned.
 */
std::string
IRC::ReplyBuilder::get_user_mode_symbol_(Channel *channel, User *user){
	return (std::string[2]){"+", "@"}[(channel->is_operator_user(user) || channel->is_voices_user(user))];
}