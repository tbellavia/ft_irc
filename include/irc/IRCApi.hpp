/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCApi.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:08:41 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/23 16:25:21 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IRC_API_HPP
# define IRC_API_HPP

# include "MasterUsers.hpp"
# include "Channels.hpp"
# include "ICmdFactory.hpp"
# include "Action.hpp"

namespace IRC
{
	class Api {
		MasterUsers m_users;
		Channels	m_channels;
		std::string m_password;
		ICmdFactory *m_cmd_factory;
	public:
		Api(std::string const &password);
		~Api();

		void connect(Socket *socket);
		void disconnect(Socket *socket);
		Action process_request(Socket *socket, std::string const &request);
	};
}



#endif