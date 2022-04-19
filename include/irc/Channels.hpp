/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:16:06 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/19 23:52:30 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
#define CHANNELS_HPP

# include "Channel.hpp"
# include <vector>
# include <map>

namespace IRC
{
	class Channels {
		std::map<std::string, Channel> m_channels;
	public:
		Channels();
		~Channels();

		void add(std::string const &name, int mode);
		void remove(std::string const &name);
		bool has(std::string const &name);

		std::vector<Channel> get_channels();
	};
}


#endif
