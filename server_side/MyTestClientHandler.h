#include <istream>
#include "ClientHandler.h"
#include "string.h"
#include "../problem_solve/Solver.h"
#include "../cache/CacheManager.h"
#include "AServer.h"

namespace server_side {


    template<class Problem, class Solution>
    class MyTestClientHandler : public ClientHandler {

        Solver<Problem, Solution>* solver;
        CacheManager* cacheManager;


    public:
        MyTestClientHandler(Solver<Problem, Solution>* solverToSet,
                            CacheManager* cacheManagerToSet) {
           this->solver = solverToSet;
           this->cacheManager = cacheManagerToSet;
        }

        virtual void handleClient(int socketId) {
            char buffer[BUFFER_SIZE];
            char response[BUFFER_SIZE];
            char *responsePtr = response;
            char *bufferPtr = buffer;

            int  n;
            if(socketId == -1) {
                return; //nothing to listen to
            }

            /* If connection is established then start communicating */
            while(true) {

                bzero(buffer, BUFFER_SIZE);
                //read bytes
                n = (int)read(socketId, buffer, (BUFFER_SIZE - sizeof(char)));


                //empty packet - lost connection
                if (n <= ZERO){
                    return;
                }
                cout << "message from client: " << buffer;
                handleMessage(bufferPtr, &responsePtr);
                cout << response << endl;

                int resultCode;
                size_t len = strlen(response);
                resultCode = (int)send(socketId, response, len, 0);

                //check message sent
                if (resultCode < ZERO) {
                    cout << "ERROR writing to socket" << endl;
                }
            }
        }


        virtual void handleMessage(char* inputStream, char** outputStream) {
            //if problem not string convert it here

            Problem problem = inputStream;
            Solution result;

            if (this->cacheManager->isSolution(inputStream)) {
                result = this->cacheManager->getSolution(inputStream);
                cout << "found on cache";
            } else {
                result = this->solver->solve(inputStream);
                this->cacheManager->saveSolution(inputStream, result);
                cout << "solver job";
            }

            string s = result;
            //if solution not string convert it here to string
            strcpy(*outputStream, s.c_str());
        }

        ~MyTestClientHandler() {
            solver = nullptr;
            cacheManager = nullptr;
        }

    };

}