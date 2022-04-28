/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 02:11:07 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/28 02:20:22 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPARSER_HPP
#define CMDPARSER_HPP

# include <string>
# include <vector>

namespace IRC
{
	class CommandParser {
		std::string				m_request;
		std::string::size_type	m_start;
		std::string::size_type	m_current;


		bool		is_at_end();
		std::string	parse_single_token();
		std::string parse_end_token();
		bool		skip_space();
		char		peek();
		char		advance();
	public:
		CommandParser(std::string const &request);

		std::vector<std::string> parse();
	};
}


#endif
