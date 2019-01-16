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

using namespace server_side;


int main(int arg, char *argv[]) {

    std::cout << "Hi, Hilla - second road good luck to us" << std::endl;

    if (arg != 2) {
        throw "no port recived for opening server";
    }

    int portNumber = atoi(argv[1]);

    /*   Expretiment experiment;
       vector<Searcher<int,POINT,string>*> searchers;
       searchers.push_back(new BestFirstSearch<int, POINT, string>());
       searchers.push_back(new DFS<int, POINT, string>());
       searchers.push_back(new BFS<int, POINT, string>());
       searchers.push_back(new AStar<int, POINT, string>());
       int x=1;
       while (x<=10){
           experiment.generateMatrix(20+x*3);
           experiment.writeMatToFile("graphs.txt");
           for(auto search:searchers){
               experiment.addSearchMethod(search);
               experiment.expirience();
               experiment.writeSolToFile("solutions.txt");
           }
           x++;

       }*/


    auto search = new AStar<int, POINT, string>;
    // delete search;

    CacheManager *cacheManager = new FileCacheManager("Matrix");
    Solver <MatrixSearchProblem, string> *solver = new SolverSearcher<int>(search);

    ClientHandler *clientHandler = new MyClientHandler<MatrixSearchProblem, string>(solver, cacheManager);
    Server *server;

    try {

        server = new MySerialServer();
        server->open(portNumber, clientHandler);


    } catch (char const *a) {
        cout << "failed to load server try reload";
    }


    return 0;
}


