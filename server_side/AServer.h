#include "Server.h"
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <strings.h>

#define BUFFER_SIZE 256
#define MAX_WAITING 5
#define ZERO 0
#define MILLISEC 1000
#define DEFAULT_TIME_PER_SEC 10


#ifndef HNJ_2NDROAD_ASERVER_H
#define HNJ_2NDROAD_ASERVER_H


namespace server_side {

    class AServer  : public Server{

    protected:
        int sockfd;
        int  timesPerSec;
        bool running;
        pthread_t threadRunningId;
        ClientHandler* clientHandler;
        pthread_mutex_t serverRunningMutex;

    public:

        virtual void stop();

        virtual void open(int port, ClientHandler* clientHandler) = 0;

        virtual void createSocket(int port, int timesPerSec);

        virtual int waitForConnection();

        virtual void listenToClient(int socketId) = 0;

        virtual void closeServer();

    };
}

#endif

