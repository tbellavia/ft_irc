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

#ifndef FILE_HPP
#define FILE_HPP

# include <string>
# include <queue>
# include "Socket.hpp"

# define CRLF "\r\n"

class File {
	class ResponseBuffer {
		std::string				m_responses;
		size_t					m_begin;
	public:
		ResponseBuffer();
		ResponseBuffer(ResponseBuffer const &other);
		ResponseBuffer &operator=(ResponseBuffer const &other);
		~ResponseBuffer();

		std::string pop();
		void push(std::string const &response);
		void seek(size_t offset);
		bool available() const;
	};
	Socket					*m_socket;
	int						m_events;
	std::string				m_buffer;
	std::queue<std::string> m_requests;
	ResponseBuffer			m_responses;
public:
	File();
	File(Socket *socket, int events);
	File(File const &other);
	File &operator=(File const &other);
	virtual ~File();

	Socket				*socket();
	std::string const	&buffer() const;
	
	void				set_event(int event);
	void				unset_event(int event);
	bool				isset_event(int event) const;
	void				clear();

	// Request Queue Interface
	void				push_request(std::string const &requests);
	void				push_response(std::string const &response);

	bool				available_request() const;
	bool				available_response() const;

	std::string			pop_request();
	std::string			pop_response();

	void seek_response(size_t offset);
};

#endif
