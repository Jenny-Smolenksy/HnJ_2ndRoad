//
// Created by jenny on 1/15/19.
//
#include "MySerialServer.h"
using namespace server_side;

#include "MyParallelServer.h"

void* threadListen(void* arg) {

    auto * params = (MyParallelServer*)arg;
    try {
        params->parallellListen();
    } catch (invalid_argument& e) {
        cout << "server disconnected" << endl;
        //  throw "server disconnected";
    } catch (const char* ex) {
        cout << ex;
    }
}

void* threadFuncClientListen(void* arg) {

    auto * params = (CLIENT_LISTEN_PARAMS*)arg;
    try {
        params->parallelServer->addClientRunning();
        params->clientHandler->handleClient(params->socketId);
        params->parallelServer->removeClientRunning();

    } catch (invalid_argument& e) {
        // cout << "server disconnected" << endl;
        //  throw "server disconnected";

        params->parallelServer->removeClientRunning();
    } catch (const char* ex) {
        cout << ex;
        params->parallelServer->removeClientRunning();
    }
}

void MyParallelServer::open(int port, ClientHandler* clientHandler) {

    this->clientHandler = clientHandler;

    createSocket(port, DEFAULT_TIME_PER_SEC);

    pthread_create(&threadRunningId, nullptr, threadListen, this);

    //pthread_join(threadRunningId, nullptr);

    while(!this->threadIdQueue.empty()) {

        pthread_t currentThreadId = threadIdQueue.front();
        pthread_join(currentThreadId, nullptr);
    }

    pthread_join(threadRunningId, nullptr);
    //close socket
    close(sockfd);
}

void MyParallelServer::listenToClient(int socketId) {

    auto * params =
            new CLIENT_LISTEN_PARAMS{this->clientHandler, socketId, this};

    pthread_t threadId;
    this->threadIdQueue.push(threadId);
    pthread_create(&threadId, nullptr, threadFuncClientListen, params);
}

MyParallelServer::~MyParallelServer() {

    try {
        stop();
    } catch (invalid_argument &e) {}
    catch (const char* c) {}
    clientHandler = nullptr;
}

void MyParallelServer::parallellListen() {
    int clientSocket;
    bool flag = true;


    timeval timeout;
    //time out only for clients after the first
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    timeval timeOutMessage;
    timeOutMessage.tv_sec = 100000000;
    timeOutMessage.tv_usec = 0;


    while (flag) {

        clientSocket = waitForConnection();

        if (clientSocket == -1) {
            //timeout
           if(this->getIsClientRunning()) {
               //cout << "other clients running";
           } else {
               flag = false;
           }
           continue;
        }

        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeOutMessage, sizeof(timeOutMessage));
        cout << "new client" << endl;
        listenToClient(clientSocket);

        //check if server requested to close
        pthread_mutex_lock(&serverRunningMutex);
        if (!running) {
            //release lock
            pthread_mutex_unlock(&serverRunningMutex);
            flag = false;
        }
        //release lock
        pthread_mutex_unlock(&serverRunningMutex);

        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    }

    cout << "time out caused server stop listening";
}

void* threadFuncStop(void* arg) {

    AServer* aServer = (AServer*)arg;
    aServer->closeServer();
}

void MyParallelServer::stop() {

    pthread_t pthreadIdClose;

    pthread_create(&pthreadIdClose, nullptr, threadFuncStop, this);
    pthread_join(pthreadIdClose, nullptr);

    while(!this->threadIdQueue.empty()) {

        pthread_t currentThreadId = threadIdQueue.front();
        pthread_join(currentThreadId, nullptr);
    }

    pthread_join(threadRunningId, nullptr);

    //close socket
    close(sockfd);
}


MyParallelServer::MyParallelServer() {
    this->countClientsRunning = 0;
    pthread_mutex_init(&clientsCountMutex, nullptr);
}

bool MyParallelServer::getIsClientRunning() {

    bool result = true;

    pthread_mutex_lock(&clientsCountMutex);

    if (this->countClientsRunning == 0) {
        result = false;
    }
    //release lock
    pthread_mutex_unlock(&clientsCountMutex);

    return result;
}

void MyParallelServer::addClientRunning() {
    pthread_mutex_lock(&clientsCountMutex);

    this->countClientsRunning++;
    //release lock
    pthread_mutex_unlock(&clientsCountMutex);

}

void MyParallelServer::removeClientRunning() {
    pthread_mutex_lock(&clientsCountMutex);

    this->countClientsRunning--;
    //release lock
    pthread_mutex_unlock(&clientsCountMutex);
}

