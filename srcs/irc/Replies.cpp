/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/08 17:31:15 by lperson-         ###   ########.fr       */
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
	std::string reply = this->build_header_(
		NumericReplies::ERR_ALREADYREGISTRED
	);
	
	reply.append(" ");
	reply.append(":You may not reregister");
	return reply;
}

/*
 * Connections replies
*/

std::string
IRC::ReplyBuilder::reply_welcome(std::string const &user_mask) {
	std::string reply = this->build_header_(NumericReplies::RPL_WELCOME);

	reply += " Welcome to the Internet Relay Network " + user_mask;
	return reply;
}

std::string
IRC::ReplyBuilder::reply_your_host(
	std::string const &hostname, std::string const &version
) {
	std::string reply = this->build_header_(NumericReplies::RPL_YOURHOST);

	reply += "Your host is " + hostname + ", running version " + version;
	return reply;
}

std::string
IRC::ReplyBuilder::reply_created(std::string const &date) {
	std::string reply = this->build_header_(NumericReplies::RPL_CREATED);

	reply += "This server was created " + date;
	return reply;
}

std::string
IRC::ReplyBuilder::reply_my_info(ConfigServer const &config) {
	std::string reply = this->build_header_(NumericReplies::RPL_MYINFO);

	reply +=
		" " + config.server_name + " " + config.server_version +
		" " + IRC_USER_MODE_STRING + " " + IRC_CHANNEL_MODE_STRING;
	return reply;
}

IRC::Actions
IRC::ReplyBuilder::connection_complete_replies(
	User *sender, ConfigServer const &config
) {
	IRC::Actions reply_queue;

	reply_queue.push(
		IRC::Action(IRC::Event::SEND, sender, this->reply_welcome(
			sender->get_mask()
		))
	);
	reply_queue.push(
		IRC::Action(IRC::Event::SEND, sender, this->reply_your_host(
			config.server_name, config.server_version
		))
	);
	reply_queue.push(
		IRC::Action(IRC::Event::SEND, sender, this->reply_created(
			config.server_creation_date
		))
	);
	reply_queue.push(
		IRC::Action(IRC::Event::SEND, sender, this->reply_my_info(config))
	);
	return reply_queue;
}

/*
 * Ping - Pong replies
*/

std::string
IRC::ReplyBuilder::reply_ping(std::string const &name) {
	return "PING " + name;
}

std::string
IRC::ReplyBuilder::reply_pong(std::string const &name) {
	return "PONG " + name;
}

std::string
IRC::ReplyBuilder::error_no_origin() {
	std::string reply = this->build_header_(NumericReplies::ERR_NOORIGIN);

	reply += " :No origin specified";
	return reply;
}

/*
 * Invite
*/

std::string
IRC::ReplyBuilder::reply_invite(
	std::string const &nickname, std::string const &channel_name
) {
	std::string reply = this->build_header_();
	
	return reply + " INVITE " + nickname + " " + channel_name;
}

std::string
IRC::ReplyBuilder::reply_inviting(
	std::string const &nickname, std::string const &channel_name
) {
	std::string reply = this->build_header_(NumericReplies::RPL_INVITING);

	return reply + " " + channel_name + nickname;
}

std::string IRC::ReplyBuilder::error_no_such_nick(std::string const &nickname)
{
	std::string reply = this->build_header_(NumericReplies::ERR_NOSUCKNICK);

	reply += " " + nickname + " :No such nick/channel";
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

// Channels error
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
IRC::ReplyBuilder::error_user_on_channel(
	std::string const &nickname, std::string const &channel_name
) {
	std::string reply = this->build_header_(NumericReplies::ERR_USERONCHANNEL);

	reply += " " + nickname + " " + channel_name + " :is already on channel";
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
IRC::ReplyBuilder::reply_user_mode(
	std::string const &user_name, std::string const &modes
) {
	std::string reply = this->build_header_();

	reply += " MODE " + user_name + " " + modes;
	return reply;
}

std::string
IRC::ReplyBuilder::error_unknown_mode(char mode)
{
	std::string reply = this->build_header_(NumericReplies::ERR_UNKNOWNMODE);

	reply += " ";
	reply.push_back(mode);
	reply += " :is unknown to me";
	return reply;
}
std::string
IRC::ReplyBuilder::error_key_set(std::string const &channel_name) {
	std::string reply = this->build_header_(NumericReplies::ERR_KEYSET);

	reply += " " + channel_name + " :Channel key already set";
	return reply;
}

std::string
IRC::ReplyBuilder::error_no_recipient(std::string const &cmd) {
	std::string reply = this->build_header_(NumericReplies::ERR_NORECIPIENT);

	reply.append(" ");
	reply.append(":No recipient given (");
	reply.append(cmd);
	reply.append(")");
	return reply;
}

std::string
IRC::ReplyBuilder::error_cannot_send_to_chan(std::string const &channel) {
	std::string reply = this->build_header_(NumericReplies::ERR_CANNOTSENDTOCHAN);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :Cannot send to channel");
	return reply;
}

std::string
IRC::ReplyBuilder::error_wild_toplevel(std::string const &mask) {
	std::string reply = this->build_header_(NumericReplies::ERR_WILDTOPLEVEL);

	reply.append(" ");
	reply.append(mask);
	reply.append(" :Wildcard in toplevel domain");
	return reply;
}

std::string
IRC::ReplyBuilder::error_no_toplevel(std::string const &mask) {
	std::string reply = this->build_header_(NumericReplies::ERR_NOTTOPLEVEL);

	reply.append(" ");
	reply.append(mask);
	reply.append(" :No toplevel domain specified");
	return reply;
}

std::string
IRC::ReplyBuilder::error_no_text_to_send() {
	std::string reply = this->build_header_(NumericReplies::ERR_NOTEXTTOSEND);

	reply.append(" :No text to send");
	return reply;
}

std::string
IRC::ReplyBuilder::reply_channel_mode_is(Channel const &channel)
{
	std::string reply = this->build_header_(NumericReplies::RPL_CHANNELMODEIS);

	reply += " " + channel.get_name() + " :+";

	std::string const mode_string = IRC_CHANNEL_MODE_STRING;
	for (std::string::size_type i = 0 ; i < mode_string.length(); ++i)
	{
		if (channel.get_mode() & (0x01 << i))
			reply += mode_string[i];
	}
	return reply;
}

std::string
IRC::ReplyBuilder::reply_channel_mode(
	std::string const &channel_name,
	std::string const &modes,
	std::vector<std::string> const &mode_parameters
)
{
	std::string reply = this->build_header_();

	reply += " MODE " + channel_name + " " + modes;
	for (std::size_t i = 0; i < mode_parameters.size(); ++i)
		reply += " " + mode_parameters[i];
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
IRC::ReplyBuilder::reply_notopic(std::string const &channel) {
	std::string reply = this->build_header_(NumericReplies::RPL_NOTOPIC);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :No topic is set");
	return reply;
}

std::string
IRC::ReplyBuilder::reply_name_reply(Channel &channel){
	std::string reply = this->build_header_(NumericReplies::RPL_NAMREPLY);
	Users::view_type users = channel.get_users();

	reply.append(" ");
	reply.append(channel.get_name());
	reply.append(" :");
	for ( ; users.first != users.second ; ++users.first ){
		// `@` -> channel operator
		// `+` -> channel voices
		User *user = *users.first;

		if (users.first != channel.begin()){
			reply.append(" ");
		}

		reply.append(get_user_mode_symbol_(user, &channel));
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
IRC::ReplyBuilder::reply_ban_list(
	std::string const &channel_name, std::string const &banid
){
	std::string reply = this->build_header_(NumericReplies::RPL_BANLIST);

	reply += " " + channel_name + " " + banid;
	return reply;
}

std::string
IRC::ReplyBuilder::reply_end_of_ban_list(std::string const &channel_name){
	std::string reply = this->build_header_(NumericReplies::RPL_ENDOFBANLIST);

	reply += " " + channel_name + " :End of ban list";
	return reply;
}

std::string
IRC::ReplyBuilder::reply_who_reply(User *user, Channel *channel) {
	// std::string reply = this->build_header_(NumericReplies::RPL_WHOREPLY);
	std::string reply;

	// :72004f985062.example.com 354 Alpha2 152 #channel Tony 172.17.0.1 72004f985062.example.com Alpha2 H@ 0 :realname
	// :85d322b2505b.example.com 352 b #channel2 b3 172.17.0.1 85d322b2505b.example.com b H@ :0 realname
	reply.append(":");
	reply.append(m_sender);
	reply.append(" ");
	reply.append(code_to_string_(NumericReplies::RPL_WHOREPLY));
	reply.append(" ");
	reply.append(m_target->get_nickname());
	// reply.append(" 152 ");


	// "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
	reply.append(" ");
	if ( channel == NULL )
		reply.append("*");
	else
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
	reply.append("H");
	reply.append(get_user_mode_symbol_(user, channel));
	reply.append(" ");
	// We don't manage server to server, the hopcount is always 0
	reply.append(":0 ");
	reply.append(user->get_realname());
	return reply;
}

std::string
IRC::ReplyBuilder::reply_end_of_who(Channel *channel) {
	// std::string reply = this->build_header_(NumericReplies::RPL_ENDOFWHO);
	std::string reply;
	

	reply.append(":");
	reply.append(m_sender);
	reply.append(" ");
	reply.append(code_to_string_(NumericReplies::RPL_ENDOFWHO));
	reply.append(" ");
	reply.append(m_target->get_nickname());
	reply.append(" ");
	if ( channel == NULL )
		reply.append("*");
	else
		reply.append(channel->get_name());
	reply.append(" :End of /WHO list.");
	return reply;
}

std::string
IRC::ReplyBuilder::reply_end_of_who(std::string const &mask) {
	std::string reply;

	reply.append(":");
	reply.append(m_sender);
	reply.append(" ");
	reply.append(code_to_string_(NumericReplies::RPL_ENDOFWHO));
	reply.append(" ");
	reply.append(m_target->get_nickname());
	reply.append(" ");
	reply.append(mask);
	reply.append(" :End of /WHO list.");
	return reply;
}

std::string
IRC::ReplyBuilder::reply_privmsg(std::string const &cmd, std::string const &msg, std::string const &channel) {
	std::string reply;

	reply.append(":");
	reply.append(m_target->get_mask());
	reply.append(" ");
	reply.append(cmd);
	reply.append(" ");
	reply.append(channel);
	reply.append(" :");
	reply.append(msg);
	return reply;
}

std::string
IRC::ReplyBuilder::reply_part(std::string const &name, std::string const &message) {
	std::string reply;

	reply.append(":");
	reply.append( m_target->get_mask() );
	reply.append(" PART ");
	reply.append(name);
	reply.append(" :\"");
	reply.append(message);
	reply.append("\"");
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
		s.append(m_target->get_nickname());
	return s;
}

/**
 * @brief Build header for non-numeric replies
 * 
 * @return std::string 
 */

std::string
IRC::ReplyBuilder::build_header_(){
	std::string s;

	s.append(":");
	s.append(m_sender);
	// TODO: Manage 0 padding.
	if ( m_target )
		// TODO: For now, header is built with ip representation, should we use
		// the hostname ? 
		s += " " + m_target->get_nickname();
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
IRC::ReplyBuilder::get_user_mode_symbol_(User *user, Channel *channel){
	if ( channel == NULL ){
		if ( user->is_server_operator() )
			return "@";
		return "";
	}
	if ( channel->is_operator_user(user) )
		return "@";
	if ( channel->is_voices_user(user) )
		return "+";
	return "";
}
