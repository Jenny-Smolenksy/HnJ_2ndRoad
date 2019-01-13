#include <utility>

#ifndef HNJ_2NDROAD_MYCLIENTHANDLER_H
#define HNJ_2NDROAD_MYCLIENTHANDLER_H

#include <istream>
#include "ClientHandler.h"
#include "string.h"
#include "../problem_solve/Solver.h"
#include "../cache/CacheManager.h"
#include "AServer.h"
#include "../search/MatrixSearchProblem.h"

#define END_MATRIX "end"

namespace server_side {

    struct Path {
        string path;
        int countSteps;
    };

    template<class Problem, class Solution>
    class MyClientHandler : public ClientHandler {

        Solver<Problem, Solution> *solver;
        CacheManager *cacheManager;

    public:
        MyClientHandler(Solver<Problem, Solution> *solverToSet, CacheManager *cacheManagerToSet) {
            this->solver = solverToSet;
            this->cacheManager = cacheManagerToSet;
        }

        //TODO push basic server tech to the father class
        void getSingleMessage(int socketId, char **buffer) {

            int n;

            bzero(*buffer, BUFFER_SIZE);
            //read bytes
            n = (int) read(socketId, *buffer, (BUFFER_SIZE - sizeof(char)));

            //empty packet - lost connection
            if (n <= ZERO) {
                throw "client disconnected";
            }

        }

        void handleClient(int socketId) override {
            int n;
            if (socketId == -1) {
                return; //nothing to listen to
            }

            /* If connection is established then start communicating */
            while (true) {
                try {
                    MatrixSearchProblem m = getSingleSearchRequest(socketId);
                    //try write down a problem
                    cacheManager->saveSolution(m.problemToString(), "good");
                    //     string result =solver->solve(m);

                    //TODO search in cache
                    //TODO search in solver
                    //TODO get result to client
                } catch (const char *ex) {
                    return;
                }
            }
        }

        MatrixSearchProblem getSingleSearchRequest(int socketId) {
            //get whole problem
            vector<string> request = getRequest(socketId);

            //get destination point
            POINT dst = getPoint(request.back());

            //remove destination point from problem
            request.pop_back();

            //get source point
            POINT src = getPoint(request.back());

            //remove source point
            request.pop_back();

            //calculate matrix
            Matrix mat = getMatrix(request);

            //test
            /* cout << "dst value is:" << endl;
             cout << mat.get(dst) << endl;

             cout << "src value is:" << endl;
             cout << mat.get(src) << endl;*/

            return MatrixSearchProblem(mat, src, dst);

        }

        vector<string> getRequest(int socketId) {
            bool isEndRequest = false;
            char buffer[BUFFER_SIZE];
            char *current = buffer;
            vector<string> request;
            //read matrix data until the end massage
            while (!isEndRequest) {
                getSingleMessage(socketId, &current);

                vector<string> splitedByEnd = Utils::splitbyEndl(buffer);

                for (const string &line:splitedByEnd) {
                    if (line == END_MATRIX) {
                        isEndRequest = true;
                        break;
                    }
                    request.push_back(line);
                }

            }
            cout << "got whole request " << endl;
            return request;

        }

        POINT getPoint(string data) {
            vector<string> info = Utils::split(move(data), ',');
            POINT point;
            point.x = atoi(info[0].data());
            point.y = atoi(info[1].data());

            cout << "point " + data + " inserted" << endl;
            return point;
        }

        Matrix getMatrix(vector<string> info) {
            Matrix mat;
            for (string line:info) {
                mat.addRow(line);
            }
            cout << "matrix inserted: " << endl;
            return mat;
        }


        ~MyClientHandler() {
            solver = nullptr;
            cacheManager = nullptr;
        }

    };
}
#endif //HNJ_2NDROAD_MYCLIENTHANDLER_H