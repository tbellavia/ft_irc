/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODEParse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:46:47 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/19 16:34:21 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_PARSE_HPP

# define CMD_MODE_PARSE_HPP

# include <vector>
# include <map>
# include <functional>
# include <string>
# include <exception>
# include "irc/Mode.hpp"

namespace IRC
{
	/**
	 * @brief This class handle all logic for parsing availables modes and
	 * their arguments.
	 *
	 * @class CmdMODEParse
	 */

	class CmdMODEParse
	{
	public:
		struct ModeComp : public std::binary_function<Mode, Mode, bool>
		{
			bool operator()(Mode const &first, Mode const &second);
		};

		class ModeUnknownException : public std::exception
		{
		public:
			ModeUnknownException(char litteral);

			const char *what() const throw();

			char	mode() const;
		private:
			char	m_litteral;
		};

		struct ArgumentMissingException : public std::exception
		{
			const char *what() const throw();
		};

		CmdMODEParse();
		explicit CmdMODEParse(
			std::string const &mode_string,
			std::vector<std::string> const &arguments,
			std::string const &authorized_modes,
			std::string const &parameters_modes = ""
		);
		CmdMODEParse(CmdMODEParse const &copy);
		~CmdMODEParse();

		std::map<Mode, bool, ModeComp> parse();

		CmdMODEParse &operator=(CmdMODEParse const &rhs);

	private:
		// Each token will be of size 1
		static std::string const	m_tokens_delimiters;

		std::string					m_mode_string;
		std::vector<std::string>	m_arguments;
		std::string					m_authorized_modes;
		std::string					m_parameters_modes;

		// Parsed arguments
		std::size_t						m_cursor;
		std::map<Mode, bool, ModeComp>	m_modes;

		Mode parse_one_(char c);
		int char_to_mode_(char c);
	};
}

#endif