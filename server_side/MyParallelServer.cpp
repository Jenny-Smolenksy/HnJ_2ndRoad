//
// Created by jenny on 1/15/19.
//
#include "MySerialServer.h"
using namespace server_side;

#include "MyParallelServer.h"

/**
 * listen thread
 * @param arg
 * @return
 */
void* threadListen(void* arg) {

    auto * params = (MyParallelServer*)arg;
    try {
        params->parallellListen();
    } catch (invalid_argument& e) {
        cout << "server disconnected" << endl;
    } catch (const char* ex) {
        cout << ex;
    }

}
/**
 * listen to client thread funciton
 * @param arg
 * @return
 */
void* threadFuncClientListen(void* arg) {

    auto * params = (CLIENT_LISTEN_PARAMS*)arg;

    params->clientHandler->handleClient(params->socketId);

    delete params;
}
/**
 * open socket on give port
 * @param port
 * @param clientHandler
 */
void MyParallelServer::open(int port, ClientHandler* clientHandler) {

    this->clientHandler = clientHandler;

    createSocket(port, DEFAULT_TIME_PER_SEC);

    //create thread opening socket
    // pthread_create(&threadRunningId, nullptr, threadListen, this);

    parallellListen();
    //wait for the thread
    // pthread_join(threadRunningId, nullptr);
}
/**
 * listen to client on given socket
 * @param socketId
 */
void MyParallelServer::listenToClient(int socketId) {

    CLIENT_LISTEN_PARAMS * params =
            new CLIENT_LISTEN_PARAMS{this->clientHandler, socketId, this};

    pthread_t threadId;
    pthread_create(&threadId, nullptr, threadFuncClientListen, params);
    this->threadIdVector.push_back(threadId);
}
/**
 * listen parallel to clients
 */
void MyParallelServer::parallellListen() {
    int clientSocket;
    bool flag = true;

    timeval timeout;
    //time out only for clients after the first
    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    timeval timeOutMessage;
    timeOutMessage.tv_sec = MESSAGE_TIMEOUT;
    timeOutMessage.tv_usec = 0;


    //while to closed
    while (flag) {

        //wait for client
        clientSocket = waitForConnection();

        //if time out or wrong input
        if (clientSocket == -1) {

            flag = false;
            stop();

            continue;
        }

        //setting timeout
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) == -1) {
            perror("ERROR on setting timeout");
        }

        listenToClient(clientSocket);
    }

    cout << "time out caused server stop listening" << endl;
}
/**
 * function thread to stop server
 * @param arg
 * @return
 */
void* threadFuncStop(void* arg) {

    AServer* aServer = (AServer*)arg;
    aServer->closeServer();
}
/**
 * stop server by request
 */
void MyParallelServer::stop() {

    pthread_t pthreadIdClose;

    //  pthread_create(&pthreadIdClose, nullptr, threadFuncStop, this);
    //  pthread_join(pthreadIdClose, nullptr);

    for(auto thread :this->threadIdVector) {

        pthread_join(thread, nullptr);
    }

    threadIdVector.clear();

    //close socket
    close(sockfd);
}

/**
 * free alocated space
 */
MyParallelServer::MyParallelServer() {
    this->clientHandler = nullptr;
    this->countClientsRunning = 0;
}

