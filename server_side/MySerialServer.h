#include "AServer.h"


namespace server_side {

    class MySerialServer : public AServer {

    public:

        virtual void listenToClient(int socketId);

        virtual void serialListen();

        virtual void open(int port, ClientHandler* clientHandler);

        virtual void stop();

        ~MySerialServer();
    };
}
