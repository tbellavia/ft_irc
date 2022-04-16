/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:53:04 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/14 23:43:20 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISELECTORVALUE_HPP
#define ISELECTORVALUE_HPP

# include <string>
# include <queue>
# include "Socket.hpp"

# define CRLF "\r\n"

class File {
	Socket					*m_socket;
	int						m_events;
	std::string				m_buffer;
	std::queue<std::string> m_requests;
public:
	File();
	File(Socket *socket, int events);
	File(File const &other);
	File &operator=(File const &other);
	virtual ~File();

	Socket				*socket();
	std::string const	&buffer() const;
	
	bool				isset(int event) const;
	void				clear();

	// Request Queue Interface
	void				push(std::string const &req);
	bool				available() const;
	std::string			pop();
};

#endif
