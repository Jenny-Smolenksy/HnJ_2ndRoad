#include <istream>
#include "ClientHandler.h"
#include "string.h"
#include "../problem_solve/Solver.h"
#include "../cache/CacheManager.h"
#include "AServer.h"

namespace server_side {

    template<class Problem, class Solution>
    class MyTestClientHandler : public ClientHandler {

        Solver<Problem, Solution> *solver;
        CacheManager *cacheManager;

    public:
        //create new handler
        MyTestClientHandler(Solver<Problem, Solution> *solverToSet,
                            CacheManager *cacheManagerToSet) {
            this->solver = solverToSet;
            this->cacheManager = cacheManagerToSet;
        }

        /**
         * handle a given socket
         * @param socketId
         */
        virtual void handleClient(int socketId) {
            char buffer[BUFFER_SIZE];
            char response[BUFFER_SIZE];
            char *responsePtr = response;
            char *bufferPtr = buffer;

            int n;
            if (socketId == -1) {
                return; //nothing to listen to
            }

            /* If connection is established then start communicating */
            while (true) {

                bzero(buffer, BUFFER_SIZE);
                //read bytes
                n = (int) read(socketId, buffer, (BUFFER_SIZE - sizeof(char)));


                //empty packet - lost connection
                if (n <= ZERO) {
                    return;
                }
                cout << "message from client: " << buffer;
                handleMessage(bufferPtr, &responsePtr);
                cout << response << endl;

                int resultCode;
                size_t len = strlen(response);
                resultCode = (int) send(socketId, response, len, 0);

                //check message sent
                if (resultCode < ZERO) {
                    cout << "ERROR writing to socket" << endl;
                }
            }
        }


        /**
         * handle singel message
         * @param inputStream
         * @param outputStream answer to client
         */
        virtual void handleMessage(char *inputStream, char **outputStream) {
            //if problem not string convert it here
            string prob = inputStream;
              if (!prob.empty() && prob[prob.length() - 1] == '\n') {
                  prob.erase(prob.length() - 1);
              }
              Problem problem = inputStream;
              Solution result;
              //check on cache
              if (this->cacheManager->isSolution(prob)) {
                  result = this->cacheManager->getSolution(prob);
                  cout << "found on cache";
              } else {
                  //solve
                  result = this->solver->solve(prob);
                  this->cacheManager->saveSolution(prob, result);
                  cout << "solver job";
              }

              //get solution
              string s = result;
              //if solution not string convert it here to string
              strcpy(*outputStream, s.c_str());

        }

        /**
         * free space
         */
        ~MyTestClientHandler() {
            solver = nullptr;
            cacheManager = nullptr;
        }

    };

}