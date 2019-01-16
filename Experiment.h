#include <utility>

//
// Created by jenny on 1/15/19.
//

#ifndef HNJ_2NDROAD_EXPERIMENT_H
#define HNJ_2NDROAD_EXPERIMENT_H

#include "search/Matrix.h"
#include "search/ISearcher.h"
#include "search/DFS.h"
#include <iostream>
#include <algorithm>
#include "cache/FileToucher.h"

/**
 * class to run a whole problem
 */
class Expretiment {
    Matrix mat;
    POINT startPoint;
    POINT endPoint;
    Searcher<int, POINT, string> *searcher;

public:
    /**
     * build matrix from a given string
     * @param mat
     * @param div
     */
    void buildMatrix(const string &mat, char div) {
        this->mat.clear();
        for (const string &line:Utils::split(mat, div)) {
            this->mat.addRow(line);
        }
        startPoint=POINT(0,0);
        endPoint=POINT(this->mat.size()-1,this->mat.size()-1);
        this->mat.assignFriends();
    }

    /**
     * generate random Matrix
     * @param n
     */
    void generateMatrix(unsigned n) {

        string mat;

        for (int k = 0; k < n; ++k) {
            string line;
            int val ;
            for (int i = 0; i < n; ++i) {
                val =rand() % 10 +1;
                line += to_string(val);
                line.push_back(',');
            }
            line.pop_back();
            line.push_back('|');
            mat += line;
        }
        buildMatrix(mat, '|');
        startPoint = POINT(0, 0);
        endPoint = POINT(n - 1, n - 1);

    }

    /**
     * add Search Method
     * @param s
     */
    void addSearchMethod(Searcher<int, POINT, string> *s) {
        this->searcher = s;
    }

    /**
     * run
     */
    void expirience() {
        mat.initial();
        SearchNode<int> *startNode = mat.get(startPoint);
        SearchNode<int> *endNode = mat.get(endPoint);
        if (!this->mat.empty() && startNode != nullptr && endNode != nullptr && searcher != nullptr) {

        }
    }

    /**
     * arrange matrix format
     * @return
     */
    string matRepesentation() {
        string matRep;
        for (char c:mat.search_base_to_string()) {
            if (c == '|') {
                matRep += "\n";
            } else {
                matRep += c;;
            }
        }
        return matRep;
    }

    /**
     * arrange solution format
     * @return
     */
    string solutionFormat() {
        string solution = to_string((int) searcher->getPathCost(mat.get(startPoint), mat.get(endPoint)));
        solution += ",";
        solution += to_string(searcher->getDiscovered());

        return solution;
    }


    /**
     * write matrix to graph file
     * @param graph
     */
    void writeMatToFile(string graph) {
        FileToucher *writer = FileToucher::getInstance();

        //graph
        writer->writeSimple(graph,to_string(endPoint.x+1));
        writer->writeSimple(graph, startPoint.pointToString());
        writer->writeSimple(graph, endPoint.pointToString());
        writer->writeSimple(graph, matRepesentation());




    }

    /**
     * write solution format to file
     * @param sol
     */
    void writeSolToFile(string sol){
        //solution
        FileToucher *writer = FileToucher::getInstance();
        writer->writeSimple(sol, solutionFormat());
    }


};

#endif //HNJ_2NDROAD_EXPERIMENT_H
