/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/06/14 18:03:55 by lperson-         ###   ########.fr       */
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
# include "Network.hpp"
# include "File.hpp"
# include "IFileObj.hpp"

class Selector {
public:
	enum {
		READ		= 0x01 << 0,
		WRITE		= 0x01 << 1,
		EXCEPT		= 0x01 << 2,
		DISCONNECT	= 0x01 << 3
	};

private:
	fd_set					m_read;
	fd_set					m_write;
	std::map<int, File*>	m_entries;
	int						m_max_fd;
public:
	Selector();
	Selector(Selector const &other);
	Selector &operator=(Selector const &other);
	~Selector();

	std::map<int, File*> const &get_entries() const;
	File *find(IFileObj *fileobj);

	void unset(IFileObj *fileobj, int events);
	void add(IFileObj *fileobj, int events);
	void remove(IFileObj *fileobj);
	std::pair<std::set<File*>, std::set<File*> > select(
		int seconds = -1, int useconds = -1
	);
};

#endif //FT_IRC_SELECTOR_HPP
