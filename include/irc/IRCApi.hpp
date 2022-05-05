/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:08:41 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/27 02:15:25 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IRC_API_HPP
# define IRC_API_HPP

# include "MasterUsers.hpp"
# include "Channels.hpp"
# include "ICmdFactory.hpp"
# include "Actions.hpp"
# include "Config.hpp"

namespace IRC
{
	class Api {
		MasterUsers 	m_users;
		Channels		m_channels;
		ConfigServer	&m_config;
		ICmdFactory		*m_cmd_factory;
	public:
		Api(ConfigServer &config);
		Api(Api const &other);
		Api &operator=(Api const &other);
		~Api();

		void connect(Socket *socket);
		void disconnect(Socket *socket);
		Actions process_request(Socket *socket, std::string const &request);
	};
}



#endif