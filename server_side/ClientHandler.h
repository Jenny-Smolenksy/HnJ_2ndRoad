#include <iosfwd>


#ifndef HNJ_2NDROAD_CLIENTHANDLER_H
#define HNJ_2NDROAD_CLIENTHANDLER_H


using namespace std;

namespace server_side {


    class ClientHandler{

    public:

        virtual void handleClient(int clientSocket) = 0;
    };
}

#endif //HNJ_2NDROAD_CLIENTHANDLER_H