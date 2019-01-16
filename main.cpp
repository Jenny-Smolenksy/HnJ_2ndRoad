
#include <iostream>
#include "Experiment.h"
#include "search/AStar.h"
#include "server_side/AServer.h"
#include "cache/CacheManager.h"
#include "cache/FileCacheManager.h"
#include "server_side/MyClientHandler.h"
#include "problem_solve/Solver.h"
#include "server_side/MySerialServer.h"
#include "search/SolverSearcher.h"
#include "server_side/MyParallelServer.h"

using namespace server_side;


int main(int arg, char *argv[]) {
    if (arg != 2) {

        cout << "no port recived for opening server" << endl;
        return 0;
    }

    int portNumber = atoi(argv[1]);


    auto search = new AStar<int, POINT, string>;
    // delete search;

    CacheManager *cacheManager = new FileCacheManager("Matrix");
    Solver <MatrixSearchProblem, string> *solver = new SolverSearcher<int>(search);

    ClientHandler *clientHandler = new MyClientHandler<MatrixSearchProblem, string>(solver, cacheManager);
    Server *server;

    try {

        server = new MyParallelServer();
        server->open(portNumber, clientHandler);


    } catch (char const *a) {
        cout << "failed to load server try reload";
    }

    delete search;
    delete cacheManager;
    delete solver;
    delete clientHandler;
    delete server;


    return 0;
}


