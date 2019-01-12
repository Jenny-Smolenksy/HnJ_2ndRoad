#include "AServer.h"
using namespace server_side;

void AServer::createSocket(int portNumber, int timesPerSec) {
    struct sockaddr_in serv_addr = {};

    //AF_INET = ipv4 , SOCK_STREAM = tcp
    sockfd = socket(AF_INET, SOCK_STREAM, ZERO);

    if (sockfd < ZERO) {
        cout << "ERROR opening socket";
        throw "ERROR opening socket";
    }

    //Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //set socket params
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port =  htons((u_int16_t )portNumber);

    //Now bind the host address using bind() call.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < ZERO) {
        cout << "ERROR on binding";
        throw "ERROR on binding";
    }
    this->timesPerSec = timesPerSec / MILLISEC;
    this->running = false;
    pthread_mutex_init(&serverRunningMutex, nullptr);
    cout << "server starting.." << endl;
}

int AServer::waitForConnection() {
    int currentSocketFd, clilen;
    struct sockaddr_in cli_addr = {};

    ::listen(sockfd, MAX_WAITING);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    currentSocketFd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (errno == EWOULDBLOCK)	{
        cout << "timeout waiting for client" << endl;
        return -1;
    }

    if (currentSocketFd < ZERO) {
        cout << "ERROR on accept" << endl;
        return -1;
    }

    //check if server requested to close
    pthread_mutex_lock(&serverRunningMutex);

    this->running = true;

    //release lock
    pthread_mutex_unlock(&serverRunningMutex);


    cout << "client connected" << endl;
    return currentSocketFd;
}

void* threadFuncStopListen(void* arg) {

    AServer* aServer = (AServer*)arg;
    aServer->closeServer();
}


void AServer::closeServer() {
    pthread_mutex_lock(&serverRunningMutex);
    running = false;
    //release lock
    pthread_mutex_unlock(&serverRunningMutex);
}

void AServer::stop() {

    pthread_t pthreadIdClose;

    pthread_create(&pthreadIdClose, nullptr, threadFuncStopListen, this);
    pthread_join(pthreadIdClose, nullptr);
    pthread_join(threadRunningId, nullptr);

    //close socket
    close(sockfd);
}