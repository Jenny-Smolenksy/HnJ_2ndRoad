#include "Server.h"

using namespace server_side;

class MySerialServer : public Server {

    virtual void open(int port, ClientHandler clientHandler);

};