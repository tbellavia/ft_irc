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
# include "Config.hpp"

namespace IRC
{
	class Server {
		ConfigServer			&m_config;
		Socket					*m_server;
		Selector				m_selector;
		std::pair<
			std::set<File*>,
			std::set<File*> >	m_ready;
		std::set<File*>			m_writers;
		std::set<File*>			m_readers;

		void sendall_(Action &action);
		void send_(Socket *socket, std::string const &response);
		void disconnectall_(Api &api, Action &action);
		void disconnect_(Api &api, Socket *socket);
		void connect_(Api &api, Socket *socket);
		void process_actions_(Api &api, Actions &actions);
		void select_();
	public:
		Server(ConfigServer &conf, bool bind_and_activate = false);
		Server(Server const &other);
		Server &operator=(Server const &other);
		~Server();

		void activate() const;
		void bind() const;
		void serve_forever(IRC::Api &api);
	};
}


#endif //FT_IRC_Server_HPP
