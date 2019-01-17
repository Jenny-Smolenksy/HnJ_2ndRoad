#ifndef HNJ_2NDROAD_SERVER_H
#define HNJ_2NDROAD_SERVER_H


#include "ClientHandler.h"

namespace server_side {

    class Server {

    public:

        virtual void stop() = 0;

        virtual void open(int port, ClientHandler* clientHandler) = 0;

        virtual ~Server() {}
    };

}

#endif