/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SelectorValue.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:53:04 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 18:14:34 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISELECTORVALUE_HPP
#define ISELECTORVALUE_HPP

# include <string>
# include "Socket.hpp"

# define CRLF "\r\n"

class SelectorValue {
	Socket			*m_socket;
	int				m_events;
	std::string		m_buffer;
public:
	SelectorValue();
	SelectorValue(Socket *socket, int events);
	SelectorValue(SelectorValue const &other);
	SelectorValue &operator=(SelectorValue const &other);
	virtual ~SelectorValue();

	Socket				*socket();
	std::string const	&buffer() const;
	
	bool				is_event_set(int event) const;
	bool				has_terminator(std::string const &terminator = CRLF) const;
	bool				full() const;

	void				append(std::string const &s);
	std::string 		flush();
	void				clear();
};

#endif
