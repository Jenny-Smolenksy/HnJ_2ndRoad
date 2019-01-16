
#include "MySerialServer.h"
#include "string.h"
using namespace server_side;

/**
 * listen thread function
 * @param arg
 * @return
 */
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

/**
 * open server on given port
 * @param port
 * @param clientHandler
 */
void MySerialServer::open(int port, ClientHandler* clientHandler) {

    this->clientHandler = clientHandler;

    createSocket(port, DEFAULT_TIME_PER_SEC);

    pthread_create(&threadRunningId, nullptr, threadFuncListen, this);

    pthread_join(threadRunningId, nullptr);

    //close socket
    close(sockfd);
}

/**
 * listen to clients one by one
 */
void MySerialServer::serialListen() {

    int clientSocket;
    bool flag = true;


    timeval timeout;
    //time out only for clients after the first
    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    timeval timeOutMessage;
    timeOutMessage.tv_sec = MESSAGE_TIMEOUT;
    timeOutMessage.tv_usec = 0;


    while (flag) {

        //wait for connection
        clientSocket = waitForConnection();

        //if time out
        if (clientSocket == -1) {
            flag = false;
            break;
        }

        //set timeout for client
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO,
                (char *)&timeOutMessage, sizeof(timeOutMessage));
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

        //set time out for next client
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    }

    cout << "time out caused server stop listening";
}
/**
 * stop server
 */
void MySerialServer::stop() {

    pthread_join(threadRunningId, nullptr);

    //close socket
    close(sockfd);
}
/**
 * listen to a given client
 * @param socketId
 */
void MySerialServer::listenToClient(int socketId) {
    clientHandler->handleClient(socketId);
    close(socketId);
}
/**
 * free space
 */
MySerialServer::~MySerialServer() {
    clientHandler = nullptr;
}

