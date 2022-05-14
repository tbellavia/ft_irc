/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/05/15 01:08:27 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tony on 05/04/2022.
//

#ifndef FT_IRC_SELECTOR_HPP
#define FT_IRC_SELECTOR_HPP

# include <sys/select.h>
# include <vector>
# include <map>
# include <set>
# include "Socket.hpp"
# include "Network.hpp"
# include "File.hpp"

class Selector {
public:
	enum {
		READ = 0x01,
		WRITE = 0x01 << 1,
		EXCEPT = 0x01 << 2,
	};

private:
	fd_set							m_read;
	fd_set							m_write;
	std::map<int, File*>	        m_entries;
	int								m_max_fd;
public:
	Selector();
	Selector(Selector const &other);
	Selector &operator=(Selector const &other);
	~Selector();

	std::map<int, File*> const &get_entries() const;
	File *find(Socket *socket);
	void add(Socket *socket, int events);
	void remove(Socket *socket);
	std::pair<std::set<File*>, std::set<File*> > select(int seconds = -1, int useconds = -1);
};

#endif //FT_IRC_SELECTOR_HPP
