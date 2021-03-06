//
// Created by jenny on 1/15/19.
//

#ifndef HNJ_2NDROAD_MYPARALLELSERVER_H
#define HNJ_2NDROAD_MYPARALLELSERVER_H

#include <queue>
#include "AServer.h"

namespace server_side {

    class MyParallelServer : public AServer {

        vector<pthread_t > threadIdVector;
        int countClientsRunning;

    public:

        MyParallelServer() ;

        void listenToClient(int socketId) override;

        virtual void parallellListen();

        void open(int port, ClientHandler* clientHandler) override;

        void stop() override;

        ~MyParallelServer(){};

    };



    struct CLIENT_LISTEN_PARAMS {
        ClientHandler* clientHandler;
        int socketId;
        MyParallelServer* parallelServer;
    };
}



#endif //HNJ_2NDROAD_MYPARALLELSERVER_H
