/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:44:16 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 00:07:29 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>
# include "NumericReplies.hpp"
# include "User.hpp"
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
		
		std::string error_no_nickname_given();
		std::string error_nickname_in_use(std::string const &nickname);
		std::string error_erroneus_nickname(std::string const &nickname);
		std::string error_nickname_collision(std::string const &nickname);
	};
}

#endif
