#include "AServer.h"

using namespace server_side;

namespace server_side {

    class MySerialServer : public AServer {

    public:

        virtual void listenToClient(int socketId);

        virtual void serialListen();

        virtual void open(int port, ClientHandler* clientHandler);

        ~MySerialServer();
    };
}
