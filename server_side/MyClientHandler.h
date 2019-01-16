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

    template<class Problem, class Solution>
    class MyClientHandler : public ClientHandler {

        Solver<Problem, Solution> *solver;
        CacheManager *cacheManager;

    public:
        /**
         * constractor crreate new client handle object
         * @param solverToSet
         * @param cacheManagerToSet
         */
        MyClientHandler(Solver<Problem, Solution> *solverToSet,
                CacheManager *cacheManagerToSet) {
            this->solver = solverToSet;
            this->cacheManager = cacheManagerToSet;
        }


        /**
         * get one buffer message
         * @param socketId
         * @param buffer
         */
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

        /**
         * handle an open socket
         * @param socketId
         */
        void handleClient(int socketId) override {
            int n;
            char response[BUFFER_SIZE];
            //check wrong input
            if (socketId == -1) {
                return; //nothing to listen to
            }
            Matrix* matrix;
                try {

                    matrix = new Matrix();
                    //create matrix by given message
                    MatrixSearchProblem m = getSingleSearchRequest(socketId, matrix);

                    string problem = m.problemToString();
                    Solution solution;

                    //check if solution in cache manager
                    if (cacheManager->isSolution(problem)) {
                        cout << "found on cache" << endl;
                        solution = cacheManager->getSolution(problem);
                    } else {
                        //solve
                        solution = solver->solve(m);
                        cacheManager->saveSolution(problem, solution);
                    }
                    //create stream to resend with solution
                    std::ostringstream stream;
                    stream << solution;
                    string solutionStr = stream.str();

                    cout << "solution: " << endl;
                    cout << solutionStr << endl;
                    int resultCode;
                    size_t len = solutionStr.length();
                    strcpy(response, solutionStr.c_str());

                    delete matrix;

                    resultCode = (int) send(socketId, response, len, 0);
                    //check message sent
                    if (resultCode < ZERO) {
                        cout << "ERROR writing to socket" << endl;
                    }

                    close(socketId);

                } catch (const char *ex) {
                        delete matrix;
                        cout << ex << endl;
                        return;
                    }
            }

            /**
             * one search reest deal
             * @param socketId
             * @param matrix
             * @return
             */
        MatrixSearchProblem getSingleSearchRequest(int socketId, Matrix *matrix) {
            //get whole problem
            MatrixSearchProblem problem;
            vector<string> request = getRequest(socketId);

            //get destination point
            POINT dst = getPoint(request.back());

            //remove destination point from problem
            request.pop_back();

            //get source point
            POINT src = getPoint(request.back());

            problem.setStartEnd(src, dst);

            //remove source point
            request.pop_back();

            problem.setMatrix(getMatrix(request, matrix));
            return problem;

        }

        /**
         * get request from client
         * @param socketId
         * @return
         */
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
            //cout << "got whole request " << endl;
            return request;

        }

        /**
         * parse data to point
         * @param data
         * @return
         */
        POINT getPoint(string data) {
            vector<string> info = Utils::split(move(data), ',');
            POINT point;
            point.x = atoi(info[0].data());
            point.y = atoi(info[1].data());

            //cout << "point " + data + " inserted" << endl;
            return point;
        }

        /**
         * create problem by request
         * @param info
         * @param mat
         * @return
         */
        ISearchable<int, POINT> *getMatrix(vector<string> info, Matrix *mat) {
            for (string line:info) {
                mat->addRow(line);
            }
            //cout << "matrix inserted: " << endl;
            return mat;
        }


        //free object
        ~MyClientHandler() {
            solver = nullptr;
            cacheManager = nullptr;
        }

    };
}
#endif //HNJ_2NDROAD_MYCLIENTHANDLER_H