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
                    getSingleSearchRequest(socketId);

                    //TODO search in cache
                    //TODO search in solver
                    //TODO get result to client
                } catch (const char *ex) {
                    return;
                }
            }
        }

        void getSingleSearchRequest(int socketId) {
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

            cout << "dst value is:" << endl;
            cout << mat.get(dst) << endl;

            cout << "src value is:" << endl;
            cout << mat.get(src) << endl;


        }

        vector<string> getRequest(int socketId) {
            bool isEndRequest = false;
            char buffer[BUFFER_SIZE];
            char *current = buffer;
            vector<string> request;
            //read matrix data until the end massage
            /*  while (!isEndRequest) {
                   getSingleMessage(socketId, &current);

                   vector<string> splitedByEnd = Utils::split(buffer, '/n');

                   for (const string &line:splitedByEnd) {
                       if (line == END_MATRIX) {
                           isEndRequest = true;
                           break;
                       }
                       request.push_back(line);
                       //mat.addRow(line);
                   }

              }*/
            while (true) {
                string line = readLine(socketId);
                if (line == END_MATRIX) {
                    break;
                }
                request.push_back(line);
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

        string readLine(int socketId) {

            string dataStr;
            bool finishLine = false;

            while (!finishLine) {
                char buf[1];
                int numBytesRead = static_cast<int>(recv(socketId, buf, sizeof(buf), 0));
                if (numBytesRead > ZERO) {
                    char c = buf[ZERO];
                    if (c == '\n') {
                        if (dataStr.length() > ZERO) {
                            //the all line readed, end while
                            finishLine = true;
                        }
                    } else dataStr += c;
                } else {
                    //empty packet - lost connection
                    throw "client disconnected";
                }

            }

            return dataStr;
        }


        ~MyClientHandler() {
            solver = nullptr;
            cacheManager = nullptr;
        }

    };
}
#endif //HNJ_2NDROAD_MYCLIENTHANDLER_H