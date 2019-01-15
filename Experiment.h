//
// Created by jenny on 1/15/19.
//

#ifndef HNJ_2NDROAD_EXPERIMENT_H
#define HNJ_2NDROAD_EXPERIMENT_H

#include "search/Matrix.h"
#include "search/ISearcher.h"
#include "search/DFS.h"

class Expretiment {
    Matrix mat;

public:
    void buildMatrix(const string &mat, char div) {
        for (const string &line:Utils::split(mat, div)) {
            this->mat.addRow(line);
        }
        this->mat.assignFriends();
    }

    void addStartEndPoint(POINT start, POINT end) {
        SearchNode<int> *startNode = mat.get(start);
        SearchNode<int> *endNode = mat.get(end);

        //Searcher<int, POINT, string> searcher* = new DFS<int, POINT, string>();

        auto *d = new DFS<int, POINT, string>();
       cout << d->search(&mat, startNode, endNode) << endl;
    }


};

#endif //HNJ_2NDROAD_EXPERIMENT_H
