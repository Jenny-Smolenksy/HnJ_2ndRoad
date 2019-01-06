#include <iosfwd>

using namespace std;

namespace server_side {


    class ClientHandler{

    public:

        virtual void handleClient(std::istream inputStream, std::ostream outputStream);
    };
}