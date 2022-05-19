/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODEParse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:46:47 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/19 10:38:57 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MODE_PARSE_HPP

# define CMD_MODE_PARSE_HPP

# include <vector>
# include <string>

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
		CmdMODEParse();
		explicit CmdMODEParse(
			std::string const &mode_string,
			std::vector<std::string> const &arguments,
			std::string const &authorized_modes
		);
		CmdMODEParse(CmdMODEParse const &copy);
		~CmdMODEParse();

		CmdMODEParse &operator=(CmdMODEParse const &rhs);

		std::vector<std::string> const &mode_list() const;

	private:
		// Each token will be of size 1
		static std::string const	m_tokens_delimiters;

		std::string					m_mode_string;
		std::vector<std::string>	m_arguments;
		std::string					m_authorized_modes;

		// Parsed arguments
		std::vector<std::string>	m_mode_lists;

		void tokenize_();
	};
}

#endif