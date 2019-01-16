#include <iostream>
#include "server_side/MyClientHandler.h"
#include "Experiment.h"
#include "cache/FileCacheManager.h"
#include "server_side/MySerialServer.h"
#include "problem_solve/StringReverser.h"
#include "search/SolverSearcher.h"
#include "search/BestFirstSearch.h"
#include "server_side/MyParallelServer.h"
#include "server_side/MyTestClientHandler.h"

using namespace server_side;


int main(int arg, char *argv[]) {

    std::cout << "Hi, Hilla - second road good luck to us" << std::endl;

    if (arg != 2) {
        throw "no port recived for opening server";
    }

    int portNumber = atoi(argv[1]);
/*
    Expretiment experiment;

     experiment.buildMatrix("1,2,5$7,3,7$6,9,1", '$');

  //  experiment.generateMatrix(10);
    auto search = new BestFirstSearch<int, POINT, string>();
    experiment.addSearchMethod(search);
    experiment.expirience();
    experiment.writeToFile("Graph", "Solutions");
    // delete search;
*/
    CacheManager *cacheManager = new FileCacheManager("Matrix");
    auto search = new DFS<int, POINT, string>();
    Solver<MatrixSearchProblem, string> *solver = new SolverSearcher<int>(search);

    ClientHandler *clientHandler = new MyClientHandler<MatrixSearchProblem, string>(solver, cacheManager);

    Solver<string, string> *solverReverse = new StringReverser();
    ClientHandler* clientHandler1 = new MyTestClientHandler<string, string>(solverReverse, cacheManager);
    Server *server;
    try {

        server = new MyParallelServer();
        server->open(portNumber, clientHandler);

    } catch (char const *a) {
        cout << "failed to load server try reload";
    }




    delete  cacheManager;
    delete search;
    delete solver;
    delete clientHandler;
    delete solverReverse;
    delete clientHandler1;
    delete server;
    return 0;
}


