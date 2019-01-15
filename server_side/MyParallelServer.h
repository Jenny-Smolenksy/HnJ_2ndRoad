//
// Created by jenny on 1/15/19.
//

#ifndef HNJ_2NDROAD_MYPARALLELSERVER_H
#define HNJ_2NDROAD_MYPARALLELSERVER_H

#include <queue>
#include "AServer.h"

namespace server_side {

    struct CLIENT_LISTEN_PARAMS {
        ClientHandler* clientHandler;
        int socketId;
    };

    class MyParallelServer : public AServer {

        queue<pthread_t > threadIdQueue;

    public:

        virtual void listenToClient(int socketId);

        virtual void parallellListen();

        virtual void open(int port, ClientHandler* clientHandler);

        virtual void stop();

        ~MyParallelServer();
    };
}



#endif //HNJ_2NDROAD_MYPARALLELSERVER_H
