/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODEParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:53:47 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/20 15:09:00 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE/CmdMODEParse.hpp"

IRC::CmdMODEParse::ModeUnknownException::ModeUnknownException(char litteral):
		m_litteral(litteral)
{
}

const char *
IRC::CmdMODEParse::ModeUnknownException::what() const throw()
{
	static char string[19] = "Unkown character";
	string[17] = m_litteral;
	string[18] = '\0';
	return string;
}

char
IRC::CmdMODEParse::ModeUnknownException::mode() const
{
	return m_litteral;
}

const char *
IRC::CmdMODEParse::ArgumentMissingException::what() const throw()
{
	return "Missing argument";
}

// the tokens that delimites differents mode lists in mode string
std::string const IRC::CmdMODEParse::m_tokens_delimiters = "+-";

IRC::CmdMODEParse::CmdMODEParse():
		m_mode_string(),
		m_arguments(),
		m_authorized_modes(),
		m_parameters_modes(),
		m_cursor(),
		m_mode_lists()
{
}

/**
 * @brief Construct a new IRC::CmdMODEParse object
 *
 * @param mode_string string that contains differents mode list (+ob-ob etc.)
 * @param arguments the arguments attached to mode list (<User> <ban mask> etc.)
 * @param authorized_modes the modes authorized in mode list
 */

IRC::CmdMODEParse::CmdMODEParse(
	std::string const &mode_string,
	std::vector<std::string> const &arguments,
	std::string const &authorized_modes,
	std::string const &parameters_modes
):
		m_mode_string(mode_string),
		m_arguments(arguments),
		m_authorized_modes(authorized_modes),
		m_parameters_modes(parameters_modes),
		m_cursor(0),
		m_mode_lists()
{
}

IRC::CmdMODEParse::CmdMODEParse(CmdMODEParse const &copy):
		m_mode_string(copy.m_mode_string),
		m_arguments(copy.m_arguments),
		m_authorized_modes(copy.m_authorized_modes),
		m_parameters_modes(copy.m_parameters_modes),
		m_cursor(copy.m_cursor),
		m_mode_lists(copy.m_mode_lists)
{
}

IRC::CmdMODEParse::~CmdMODEParse()
{
}

/**
 * @brief Parse the mode string with its arguments into vector of mode lists
 */

std::vector<
	std::pair<std::vector<IRC::Mode>, bool>
>
IRC::CmdMODEParse::parse()
{
	if (!m_mode_lists.empty())
		return m_mode_lists;

	std::vector<std::string>	mode_lists = this->tokenize_();
	for (std::size_t i = 0; i < mode_lists.size(); ++i)
	{
		std::vector<Mode>			mode_list;
		bool is_adding = true;
		std::size_t d = 0;
		if (m_tokens_delimiters.find(mode_lists[i][d]) != std::string::npos)
		{
			if (mode_lists[i][d] == '-')
				is_adding = false;
			++d;
		}

		for (; d < mode_lists[i].length(); ++d)
		{
			Mode mode = this->parse_one_(mode_lists[i][d]);
			mode_list.push_back(mode);
		}

		m_mode_lists.push_back(std::make_pair(mode_list, is_adding));
	}
	return m_mode_lists;
}

/**
 * @brief Return mode lists that begins with delimiters (+ or -)
 * 
 * @return std::vector<std::string> 
 */

std::vector<std::string> IRC::CmdMODEParse::tokenize_()
{
	std::vector<std::string> mode_lists;
	for (std::size_t i = 0, new_pos; i < m_mode_string.length(); i = new_pos)
	{
		new_pos = i;
		if (
			m_tokens_delimiters.find(
				m_mode_string[new_pos])
			!= std::string::npos
		)
		{
			++new_pos;
		}

		while (
			new_pos < m_mode_string.length()
			&& m_tokens_delimiters.find(
				m_mode_string[new_pos]
			) == std::string::npos
		)
		{
			++new_pos;
		}

		mode_lists.push_back(m_mode_string.substr(i, new_pos - i));
	}
	return mode_lists;
}

#include <iostream>

/**
 * @brief try to parse and construct one Mode struct
 *
 * @param c the mode in litteral form
 * @return IRC::Mode the mode structure with parameter and value filled
 */

IRC::Mode IRC::CmdMODEParse::parse_one_(char c)
{
	int value = this->char_to_mode_(c);
	if (value < 0)
	{
		throw ModeUnknownException(c);
	}

	std::string parameter = "";
	if (m_parameters_modes.find(c) != std::string::npos)
	{
		if (m_cursor >= m_arguments.size())
		{
			throw ArgumentMissingException();
		}

		parameter = m_arguments[m_cursor];
		++m_cursor;
	}

	return Mode(value, c, parameter);
}

/**
 * @brief Character c to mode
 * 
 * @param c the character to converts
 * @return the actual mode value or -1 if inexistant
 */

int IRC::CmdMODEParse::char_to_mode_(char c)
{
	for (std::string::size_type i = 0; i < m_authorized_modes.length(); ++i)
	{
		if (m_authorized_modes[i] == c)
			return (1UL << i);
	}

	return -1;
}


IRC::CmdMODEParse &IRC::CmdMODEParse::operator=(CmdMODEParse const &rhs)
{
	if (this == &rhs)
		return *this;

	m_mode_string = rhs.m_mode_string;
	m_arguments = rhs.m_arguments;
	m_authorized_modes = rhs.m_authorized_modes;
	m_parameters_modes = rhs.m_parameters_modes;
	m_cursor = rhs.m_cursor;
	m_mode_lists = rhs.m_mode_lists;

	return *this;
}
