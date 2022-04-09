//
// Created by tony on 09/04/2022.
//

#ifndef FT_IRC_IRCSERVER_HPP
#define FT_IRC_IRCSERVER_HPP

# include <string>
# include <iostream>
# include "Socket.hpp"
# include "Selector.hpp"

class IRCServer {
    static const int LISTEN_MAX = 10;
    std::string m_host;
    std::string m_port;
    Socket      *m_server;
    Selector    m_selector;
public:
    IRCServer(std::string const &host, std::string const &port, bool bind_and_activate = false)
        : m_host(host), m_port(port), m_server(Socket::create_tcp_socket()), m_selector()
    {
        int enable = true;

        m_server->setsockopt(SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        m_server->set_blocking(false);
        if ( bind_and_activate ){
            this->bind();
            this->activate();
        }
    }

    IRCServer(IRCServer const &other)
        : m_host(other.m_host), m_port(other.m_port), m_server(other.m_server), m_selector(other.m_selector) { }

    IRCServer &operator=(IRCServer const &other) {
        if ( this == &other )
            return *this;
        m_host = other.m_host;
        m_port = other.m_port;
        m_server = other.m_server;
        m_selector = other.m_selector;
        return *this;
    }

    void activate() const {
        std::cout << "Listening on " << m_host << ":" << m_port << std::endl;
        m_server->listen(IRCServer::LISTEN_MAX);
    }

    void bind() const {
        m_server->bind(m_host, m_port);
    }

    void send_all(std::vector<Selector::SelectorValue*> &values, std::string const &msg) const {
        std::vector<Selector::SelectorValue*>::iterator it = values.begin();

        for ( ; it != values.end() ; ++it ){
            (*it)->socket()->send(msg);
        }
    }

    void serve_forever() {
        std::pair<std::vector<Selector::SelectorValue*>,
                std::vector<Selector::SelectorValue*>>   ready;
        std::vector<Selector::SelectorValue*>            readers;
        std::vector<Selector::SelectorValue*>            writers;
        std::vector<Selector::SelectorValue*>::iterator  select_it;
        ssize_t                                         bytes = 0;

        m_selector.add(m_server, Selector::READ);
        while ( true ){
            ready = m_selector.select();
            readers = ready.first;
            writers = ready.second;

            for ( select_it = readers.begin() ; select_it != readers.end() ; ++select_it ){
                Selector::SelectorValue *select_value = *select_it;
                Socket                  *socket = select_value->socket();
                std::string             buffer;

                if ( *socket == *m_server ){
                    Socket *client = m_server->accept();

                    std::cout << "New connection from " << client->storage() << std::endl;
                    client->set_blocking(false);
                    m_selector.add(client, Selector::READ | Selector::WRITE);
                } else {
                    if ( (bytes = socket->recv(buffer)) <= 0 ){
                        // Connection shutdown
                        if ( bytes == 0 ){
                            std::cout << "Client has closed the connection" << std::endl;
                        }
                        // Errors
                        m_selector.remove(socket);
                        Socket::release(&socket);
                    } else {
                        // Received something
                        select_value->append( buffer );

                        // End of packets
                        if ( select_value->has_terminator() ){
                            std::string cmd = select_value->flush();

                            std::cout << "Command: " << cmd << std::endl;
                            this->send_all(writers, cmd);
                        }
                    }
                }
            }
        }
    }
};

#endif //FT_IRC_IRCSERVER_HPP
