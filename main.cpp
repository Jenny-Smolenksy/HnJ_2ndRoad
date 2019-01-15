#include <iostream>
#include "server_side/MyClientHandler.h"
#include "Experiment.h"
#include "cache/FileCacheManager.h"
#include "server_side/MySerialServer.h"
#include "problem_solve/StringReverser.h"
#include "search/SolverSearcher.h"
using namespace server_side;


int main(int arg, char *argv[]) {

    std::cout << "Hi, Hilla - second road good luck to us" << std::endl;

    if (arg != 2) {
        throw "no port recived for opening server";
    }

    int portNumber = atoi(argv[1]);

    Expretiment experiment;

    // experiment.buildMatrix("1,2,3$4,5,6$7,8,9", '$');
    experiment.generateMatrix(10);
    auto search = new DFS<int, POINT, string>();
    experiment.addSearchMethod(search);
    experiment.expirience();
    experiment.writeToFile("Graph", "Solutions");
    // delete search;

    CacheManager *cacheManager = new FileCacheManager("Matrix");
    Solver<MatrixSearchProblem, string> *solver = new SolverSearcher<int >(search);

    ClientHandler *clientHandler = new MyClientHandler<MatrixSearchProblem, string>(solver, cacheManager);
    Server *server;

    try {

        server = new MySerialServer();
        server->open(portNumber, clientHandler);


    } catch (char const *a) {
        cout << "failed to load server try reload";
    }


    Expretiment experiment1;
    //  experiment1.buildMatrix("0,1,6,2,8,2,9,4,8,7,5,9,8,0,1,3,6$4,1,0,9,10,0,7,9,0,1,2,8,9,3,10,6,7$1,7,8,9,1,0,1,10,10,0,10,1,0,10,3,7,5$0,7,6,9,10,5,10,6,3,8,0,7,9,7,1,7,1$9,1,3,5,6,0,10,4,1,7,4,6,6,2,8,10,5$2,2,1,1,6,0,6,4,9,5,6,10,7,3,3,10,5$3,0,3,10,1,8,10,4,9,4,9,0,3,1,0,3,8$4,1,4,8,9,1,9,3,7,8,5,0,5,1,4,4,0$-1,3,9,5,5,10,2,3,2,8,10,3,5,8,6,3,2$1,4,8,10,9,6,0,4,0,0,5,2,10,3,6,8,4$0,6,2,7,1,6,4,3,4,7,6,2,7,0,5,10,1$9,3,0,8,8,6,7,8,0,0,1,6,3,6,4,6,9$9,6,3,6,7,3,9,5,10,6,7,1,3,6,9,10,2$7,4,3,5,4,3,6,6,6,7,2,8,4,1,6,8,0$1,2,1,2,5,2,7,0,9,3,3,4,10,2,1,7,9$6,5,0,3,4,10,3,3,0,0,5,8,0,1,9,0,9$3,2,2,3,0,4,9,3,5,3,6,5,8,4,7,6,7$", '$');
    experiment1.buildMatrix("1,2,3$4,5,6$7,8,9$10,11,12$",'$');
    POINT* start = new POINT(0,0);
    POINT* end = new POINT(2,2);
    experiment1.addStartEndPoint(*start, *end);
    auto search1 = new DFS<int, POINT, string>();
    experiment1.addSearchMethod(search1);
    experiment1.expirience();





    /*
   while (getline(cin, problem)) {
       bool c = x->isSolution(problem);
       if (c) {
           sol = x->getSolution(problem);
           std::cout << "exict" << std::endl;
       } else {
           StringRevrser solver;
           sol = solver.solve(problem);
           x->saveSolution(problem, sol);
           std::cout << "new" << std::endl;
       }
       std::cout << sol << std::endl;
   }
    */

    return 0;
}


