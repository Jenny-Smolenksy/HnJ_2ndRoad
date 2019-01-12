#include <iostream>
#include "cache/FileCacheManager.h"
#include "server_side/MySerialServer.h"
#include "server_side/MyClientHandler.h"
#include "problem_solve/StringReverser.h"
#include "server_side/MyTestClientHandler.h"



    using namespace server_side;



        int main(int arg, char *argv[]) {

            std::cout << "Hi, Hilla - second road good luck to us" << std::endl;

            if (arg != 2) {
                throw "no port recived for opening server";
            }

            int portNumber = std::atoi(argv[1]);


            CacheManager *cacheManager = new FileCacheManager("reverse");
            string sol;
            string problem;
            Solver<string, string>* solver = new StringReverser();

            ClientHandler *clientHandler =
                    new MyTestClientHandler<string, string>(solver, cacheManager);
            Server *server;

            try {

                server = new MySerialServer();
                server->open(portNumber, clientHandler);


            } catch (char const* a) {
                cout << "failed to load server try reload";
            }

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


