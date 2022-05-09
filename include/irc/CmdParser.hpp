/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 02:11:07 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/05 23:11:44 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPARSER_HPP
#define CMDPARSER_HPP

# include <string>
# include <vector>

namespace IRC
{
	class CmdParser {
		std::string				m_request;
		std::string::size_type	m_start;
		std::string::size_type	m_current;


		bool		is_at_end();
		std::string	parse_single_token();
		std::string parse_end_token();
		bool		skip_space();
		bool		is_delim(char c);
		char		peek();
		char		advance();
	public:
		CmdParser(std::string const &request);
		CmdParser(CmdParser const &other);
		CmdParser &operator=(CmdParser const &other);
		~CmdParser();

		std::vector<std::string> parse();
	};
}


#endif
