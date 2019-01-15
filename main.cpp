#include <iostream>
#include "cache/FileCacheManager.h"
#include "server_side/MySerialServer.h"
#include "server_side/MyClientHandler.h"
#include "problem_solve/StringReverser.h"
#include "server_side/MyTestClientHandler.h"
#include "Experiment.h"

using namespace server_side;


int main(int arg, char *argv[]) {

    std::cout << "Hi, Hilla - second road good luck to us" << std::endl;

    if (arg != 2) {
        throw "no port recived for opening server";
    }

    int portNumber = atoi(argv[1]);

    Expretiment experiment;
    experiment.buildMatrix("1,2,3$4,5,6$7,8,9", '$');
    experiment.addStartEndPoint(POINT(0,0),POINT(2,1));
    auto search =new DFS<int, POINT, string>();
    experiment.addSearchMethod(search);
    experiment.expirience();
    experiment.writeToFile("Graph","Solutions");
    delete search;



/*
    CacheManager *cacheManager = new FileCacheManager("reverse");
    string sol;
    string problem;
    Solver<string, string> *solver = new StringReverser();

    ClientHandler *clientHandler = new MyClientHandler<string, string>(solver, cacheManager);
    Server *server;

    try {

        server = new MySerialServer();
        server->open(portNumber, clientHandler);


    } catch (char const *a) {
        cout << "failed to load server try reload";
    }
*/
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


