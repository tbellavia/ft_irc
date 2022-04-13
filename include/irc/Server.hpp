//
// Created by tony on 09/04/2022.
//

#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

# include <string>
# include <iostream>
# include "../network/Socket.hpp"
# include "../network/Selector.hpp"
# include "Channels.hpp"
# include "User.hpp"

namespace IRC
{
	class Server {
		static const int	LISTEN_MAX = 10;
		std::string					m_host;
		std::string					m_port;
		Socket						*m_server;
		Selector					m_selector;
		Channels					m_channels;
		std::map<Socket*, User*>	m_users;
	public:
		Server(std::string const &host, std::string const &port, bool bind_and_activate = false);
		Server(Server const &other);
		Server &operator=(Server const &other);

		void activate() const;
		void bind() const;
		void serve_forever();
	};
	
}


#endif //FT_IRC_Server_HPP
