
#include "MySerialServer.h"
#include "string.h"
using namespace server_side;

void* threadFuncListen(void* arg) {

    MySerialServer* params = (MySerialServer*)arg;
    try {
        params->serialListen();
    } catch (invalid_argument& e) {
        cout << "server disconnected" << endl;
      //  throw "server disconnected";
    } catch (const char* ex) {
        cout << ex;
    }
}


void MySerialServer::open(int port, ClientHandler* clientHandler) {

    this->clientHandler = clientHandler;

    createSocket(port, DEFAULT_TIME_PER_SEC);

    pthread_create(&threadRunningId, nullptr, threadFuncListen, this);


}


void MySerialServer::serialListen() {

    int clientSocket;
    bool flag = true;


    timeval timeout;
    //time out only for clients after the first
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    timeval timeOutMessage;
    timeOutMessage.tv_sec = 100000000;
    timeOutMessage.tv_usec = 0;


    while (flag) {

        clientSocket = waitForConnection();

        if (clientSocket == -1) {
            flag = false;
            break;
        }

        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeOutMessage, sizeof(timeOutMessage));
        listenToClient(clientSocket);

        cout << "client disconnected" << endl;

        //check if server requested to close
        pthread_mutex_lock(&serverRunningMutex);
        if (running == false) {
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

void MySerialServer::stop() {

    pthread_join(threadRunningId, nullptr);

    //close socket
    close(sockfd);
}

void MySerialServer::listenToClient(int socketId) {
    clientHandler->handleClient(socketId);
    close(socketId);
}

MySerialServer::~MySerialServer() {
    clientHandler = nullptr;
}