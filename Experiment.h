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


class Expretiment {
    Matrix mat;
    POINT startPoint;
    POINT endPoint;
    Searcher<int, POINT, string> *searcher;

public:
    void buildMatrix(const string &mat, char div) {
        this->mat.clear();
        for (const string &line:Utils::split(mat, div)) {
            this->mat.addRow(line);
        }
        startPoint=POINT(0,0);
        endPoint=POINT(this->mat.size()-1,this->mat.size()-1);
        this->mat.assignFriends();
    }

    void generateMatrix(unsigned n) {

        string mat;

        for (int k = 0; k < n; ++k) {
            string line;
            for (int i = 0; i < n; ++i) {
                line += to_string(rand() % 10);
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

    void addSearchMethod(Searcher<int, POINT, string> *s) {
        this->searcher = s;
    }

    void expirience() {
        SearchNode<int> *startNode = mat.get(startPoint);
        SearchNode<int> *endNode = mat.get(endPoint);
        if (!this->mat.empty() && startNode != nullptr && endNode != nullptr && searcher != nullptr) {

            cout << "route: " ;
            cout << searcher->search(&mat, startNode, endNode) << endl;

            cout << "amount of nodes: " << searcher->getPathNodeAmount(startNode, endNode) << endl;
            cout << "path cose: " << searcher->getPathCost(startNode, endNode) << endl;
            //TODO write mat to mat file
            //TODO write solution;
        }
    }

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

    string solutionFormat() {
        string solution = to_string((int) searcher->getPathCost(mat.get(startPoint), mat.get(endPoint)));
        solution += ",";
        solution += to_string(searcher->getPathNodeAmount(mat.get(startPoint), mat.get(endPoint)));

        return solution;
    }


    void writeToFile(string graph, string solutions) {
        FileToucher *writer = FileToucher::getInstance();

        //graph
        writer->writeSimple(graph, startPoint.pointToString());
        writer->writeSimple(graph, endPoint.pointToString());
        writer->writeSimple(graph, matRepesentation());

        //solution
        writer->writeSimple(solutions, solutionFormat());


    }


};

#endif //HNJ_2NDROAD_EXPERIMENT_H
