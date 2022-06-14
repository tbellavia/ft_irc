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
# include "SignalFD.hpp"

namespace IRC
{
	class Server {
		ConfigServer			&m_config;
		Socket					*m_server;
		SignalFD				*m_signalfd;
		Selector				m_selector;
		std::pair<
			std::set<File*>,
			std::set<File*> >	m_ready;
		std::set<File*>			m_writers;
		std::set<File*>			m_readers;
		Api						&m_api;
		bool					m_continue;


		void sendall_(Action &action);
		void push_send_(Socket *socket, std::string const &response);

		void disconnectall_(Action const &action);
		// Push disconnect request into File
		void push_disconnect_(Socket *socket);
		// Disconnect a socket
		void disconnect_socket_(Socket *socket);
		
		// Connect a socket to the underlying services
		void connect_socket_(Socket *socket);

		void handle_actions_(Actions &actions);
		
		void select_();

		void read_requests_();
		void write_responses_();
		void finish_requests_();
	public:
		Server(ConfigServer &conf, Api &api, bool bind_and_activate = false);
		Server(Server const &other);
		Server &operator=(Server const &other);
		~Server();

		void activate() const;
		void bind() const;
		void serve_forever();
		void stop();
	};
}


#endif //FT_IRC_Server_HPP
