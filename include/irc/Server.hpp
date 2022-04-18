//
// Created by tony on 09/04/2022.
//

#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

# include <string>
# include <iostream>
# include "Socket.hpp"
# include "Selector.hpp"
# include "IRCApi.hpp"

namespace IRC
{
	class Server {
		static const int	LISTEN_MAX = 10;
		std::string			m_host;
		std::string			m_port;
		std::string			m_pass;
		Socket				*m_server;
		Selector			m_selector;
	public:
		Server();
		Server(std::string const &host, std::string const &port, std::string const &pass, bool bind_and_activate = false);
		Server(Server const &other);
		Server &operator=(Server const &other);

		void activate() const;
		void bind() const;
		void serve_forever(IRC::Api &api);
		void process_request(IRC::Api &api, Socket *sender, std::string const &request);
	};
}


#endif //FT_IRC_Server_HPP
