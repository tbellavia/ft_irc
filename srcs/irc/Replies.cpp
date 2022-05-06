/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:05 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/07 00:41:53 by bbellavi         ###   ########.fr       */
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
IRC::ReplyBuilder::reply_topic(std::string const &channel, std::string const &topic){
	std::string reply = this->build_header_(NumericReplies::RPL_TOPIC);

	reply.append(" ");
	reply.append(channel);
	reply.append(" :");
	reply.append(topic);
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
IRC::ReplyBuilder::code_to_string_(int digit){
	std::string a, b, c;

	a = TO_CHAR(digit);
	digit /= 10;
	b = TO_CHAR(digit);
	digit /= 10;
	c = TO_CHAR(digit);
	return c + b + a;
}