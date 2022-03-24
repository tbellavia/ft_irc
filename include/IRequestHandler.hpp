//
// Created by tony on 24/03/2022.
//

#ifndef FT_IRC_REQUEST_HANDLER_HPP
#define FT_IRC_REQUEST_HANDLER_HPP

# include "Socket.hpp"

class IRequestHandler {
protected:
    Socket *m_socket;
public:
    virtual void setup() = 0;
    virtual void handle() = 0;
    virtual void finish() = 0;
};

#endif
