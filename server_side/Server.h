#include "ClientHandler.h"

namespace server_side {


    class Server {

        virtual void open(int port, ClientHandler clientHandler);

        virtual void stop();
    };

}