/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODEParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:53:47 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/19 09:45:49 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE/CmdMODEParse.hpp"

// the tokens that delimites differents mode lists in mode string
std::string const IRC::CmdMODEParse::m_tokens_delimiters = "+-";

IRC::CmdMODEParse::CmdMODEParse():
		m_mode_string(),
		m_arguments(),
		m_authorized_modes(),
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
	std::string const &authorized_modes
):
		m_mode_string(mode_string),
		m_arguments(arguments),
		m_authorized_modes(authorized_modes),
		m_mode_lists()
{
	// set mode lists
	this->tokenize_();
}

IRC::CmdMODEParse::CmdMODEParse(CmdMODEParse const &copy):
		m_mode_string(copy.m_mode_string),
		m_arguments(copy.m_arguments),
		m_authorized_modes(copy.m_authorized_modes)
{
}

IRC::CmdMODEParse::~CmdMODEParse()
{
}

std::vector<std::string> const &IRC::CmdMODEParse::mode_list() const
{
	return m_mode_lists;
}

/**
 * @brief tokenize mode_argument into differents mode lists
 *
 * Each mode list is a valid successions of mode adding or mode deletions
 */

void IRC::CmdMODEParse::tokenize_()
{
	for (
		std::size_t i = 0, new_position = i;
		i < m_mode_string.length();
		i = new_position
	)
	{
		new_position = i;
		// If delimiter advance 1
		if (
			m_tokens_delimiters.find(
				m_mode_string[new_position]
			) != std::string::npos
		)
		{
			++new_position;
		}

		// advance until delimiter
		while (
			m_tokens_delimiters.find(
				m_mode_string[new_position]
			) == std::string::npos
		)
		{
			++new_position;
		}

		m_mode_lists.push_back(m_mode_string.substr(i, new_position - i));
	}
}

IRC::CmdMODEParse &IRC::CmdMODEParse::operator=(CmdMODEParse const &rhs)
{
	if (this == &rhs)
		return *this;

	m_mode_string = rhs.m_mode_string;
	m_arguments = rhs.m_arguments;
	m_authorized_modes = rhs.m_authorized_modes;
	return *this;
}
