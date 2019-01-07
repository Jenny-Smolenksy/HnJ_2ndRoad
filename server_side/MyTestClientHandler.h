#include "ClientHandler.h"
#include "../problem_solve/Solver.h"
#include "../cache/CacheManager.h"

using namespace server_side;


template <class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {

    Solver<Problem, Solution> solver;
    CacheManager<Problem, Solution> cacheManager;

public:
    MyTestClientHandler(Solver<Problem, Solution> solverToSet, CacheManager<Problem, Solution> cacheManagerToSet);

    ~MyTestClientHandler();

    virtual void handleClient(std::istream inputStream, std::ostream outputStream);

};