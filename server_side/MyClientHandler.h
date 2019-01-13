#ifndef HNJ_2NDROAD_MYCLIENTHANDLER_H
#define HNJ_2NDROAD_MYCLIENTHANDLER_H

#include <istream>
#include "ClientHandler.h"
#include "string.h"
#include "../problem_solve/Solver.h"
#include "../cache/CacheManager.h"
#include "AServer.h"
#include "../search/MatrixSearchProblem.h"
#define END_MATRIX_WITH_BREAK "end\n"
#define END_MATRIX "end"

namespace server_side {

    struct Path {
        string path;
        int countSteps;
    };

    template<class Problem, class Solution>
    class MyClientHandler : public ClientHandler {

        Solver <Problem, Solution> *solver;
        CacheManager *cacheManager;

    public:
        MyClientHandler(Solver <Problem, Solution> *solverToSet,
                            CacheManager *cacheManagerToSet) {
            this->solver = solverToSet;
            this->cacheManager = cacheManagerToSet;
        }

        void getSingleMessage(int socketId, char** buffer) {

            int n;

            bzero(*buffer, BUFFER_SIZE);
            //read bytes
            n = (int)read(socketId, *buffer, (BUFFER_SIZE - sizeof(char)));

            //empty packet - lost connection
            if (n <= ZERO){
                throw "client disconnected";
            }

        }

        virtual void handleClient(int socketId) {
            int  n;
            if(socketId == -1) {
                return; //nothing to listen to
            }

            /* If connection is established then start communicating */
            while(true) {
                try {
                    getSingleSearchRequest(socketId);

                    //search in cache
                    //search in solver
                    //get result to client
                } catch (const char* ex) {
                    return;
                }
            }
        }

        void getSingleSearchRequest(int socketId) {

            bool isEndMatrix = false;
            char buffer[BUFFER_SIZE];
            char* current = buffer;

            /* If connection is established then start communicating */
            do {


               getSingleMessage(socketId, &current);
               ///

               if (strcmp(buffer, END_MATRIX) == 0
                    || strcmp(buffer, END_MATRIX_WITH_BREAK) == 0) {

                   isEndMatrix = true;
               }
                else {
                   insertToMatrix(current);
                }

            } while (isEndMatrix == false);

            //get start point
            getSingleMessage(socketId, &current);
            insertStartPoint(current);
            //get end point
            getSingleMessage(socketId, &current);
            insertEndPoint(current);
        }

        void insertToMatrix(string s) {
            cout << "will insert to matrix: " << s;
        }

        void insertStartPoint(string s) {
            cout << "start point will be " << s;
        }

        void insertEndPoint(string s) {
            cout << "end point will be " << s;
        }

        ~MyClientHandler(){
            solver = nullptr;
            cacheManager = nullptr;
        }

    };
}
#endif //HNJ_2NDROAD_MYCLIENTHANDLER_H