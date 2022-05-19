/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODEParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:53:47 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/19 16:34:58 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE/CmdMODEParse.hpp"

/**
 * @brief Check if mode first is less than mode second
 * 
 * @param first the first mode to compare
 * @param second the second mode to compare
 * @return true if first is less than second
 * @return false if first is not less than second
 */

bool
IRC::CmdMODEParse::ModeComp::operator()(Mode const &first, Mode const &second)
{
	return \
		first.litteral < second.litteral || \
		first.value < second.value || \
		first.parameter < second.parameter;
}

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
		m_modes()
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
		m_modes()
{
}

IRC::CmdMODEParse::CmdMODEParse(CmdMODEParse const &copy):
		m_mode_string(copy.m_mode_string),
		m_arguments(copy.m_arguments),
		m_authorized_modes(copy.m_authorized_modes),
		m_parameters_modes(copy.m_parameters_modes),
		m_cursor(copy.m_cursor),
		m_modes(copy.m_modes)
{
}

IRC::CmdMODEParse::~CmdMODEParse()
{
}

/**
 * @brief Parse the mode string with its arguments into map of Modes
 *
 * @return std::map<IRC::Mode, bool, IRC::CmdMODEParse::ModeComp>
 * the first value of the pair is the Mode itself, the second if we add it or
 * delete it.
 */

/**
 * The idea of using the map is to cancel modes that do the same thing twice
 * and cancel the mode that do reverse things between each others.
 */

std::map<IRC::Mode, bool, IRC::CmdMODEParse::ModeComp>
IRC::CmdMODEParse::parse()
{
	bool is_adding = true;
	for (std::size_t i = 0; i < m_mode_string.length(); ++i)
	{
		if (m_tokens_delimiters.find(m_mode_string[i]) != std::string::npos)
		{
			if (m_mode_string[i] == '-')
				is_adding = false;
			else
				is_adding = true;
		}
		else
		{
			Mode new_mode = this->parse_one_(m_mode_string[i]);

			// If already in map and their values differs we erase them
			std::pair<std::map<Mode, bool, ModeComp>::iterator, bool> r;
			r = m_modes.insert(std::make_pair(new_mode, is_adding));
			if (!r.second && r.first->second != is_adding)
				m_modes.erase(r.first);
		}
	}
	return m_modes;
}

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
		throw ModeUnknownException(c);

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
	m_modes = rhs.m_modes;

	return *this;
}
