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
		ConfigServer		&m_config;
		Socket				*m_server;
		Selector			m_selector;

		void sendall(Action &action);
		void send(Socket *socket, std::string const &response);
		void disconnectall(Api &api, Action &action);
		void disconnect(Api &api, Socket *socket);
		void connect(Api &api, Socket *socket);
		void process_actions(Api &api, Actions &actions);
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
