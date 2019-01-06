#include "ClientHandler.h"
#include "../problem_solve/Solver.h"
#include "../cache/CacheManager.h"

using namespace server_side;


template <class Type>
class MyTestClientHandler : public ClientHandler {

    Solver<Type> solver;
    CacheManager<Type> cacheManager;

public:
    MyTestClientHandler(Solver<Type> solverToSet, CacheManager<Type> cacheManagerToSet);

    ~MyTestClientHandler();

    virtual void handleClient(std::istream inputStream, std::ostream outputStream);

};