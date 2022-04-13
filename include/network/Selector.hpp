/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:31:22 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/13 16:57:54 by bbellavi         ###   ########.fr       */
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
# include "Socket.hpp"
# include "Network.hpp"
# include "SelectorValue.hpp"

class Selector {
public:
	enum {
		READ = 0x01,
		WRITE = 0x01 << 1,
		EXCEPT = 0x01 << 2,
	};

	typedef std::vector<SelectorValue*> ready_type;
private:
	fd_set							m_read;
	fd_set							m_write;
	std::map<int, SelectorValue*>	m_entries;
	int								m_max_fd;
public:
	Selector();
	Selector(Selector const &other);
	Selector &operator=(Selector const &other);
	~Selector();

	std::map<int, SelectorValue*> const &get_entries() const;
	void add(Socket *socket, int events);
	void remove(Socket *socket);
	std::pair<ready_type, ready_type> select(int seconds = -1, int useconds = -1);
};

#endif //FT_IRC_SELECTOR_HPP
