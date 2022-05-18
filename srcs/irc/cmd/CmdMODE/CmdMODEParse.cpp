/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMODEParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:53:47 by lperson-          #+#    #+#             */
/*   Updated: 2022/05/18 16:02:30 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/cmd/CmdMODE/CmdMODEParse.hpp"

IRC::CmdMODEParse::CmdMODEParse():
		m_mode_string(),
		m_arguments(),
		m_authorized_modes()
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
		m_authorized_modes(authorized_modes)
{
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
