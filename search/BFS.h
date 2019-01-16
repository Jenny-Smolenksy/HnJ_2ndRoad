//
// Created by jenny on 1/15/19.
//

#ifndef HNJ_2NDROAD_BFS_H
#define HNJ_2NDROAD_BFS_H

#include "Searcher.h"
#include <queue>

template <class Type, class SearchType, class Solution>
class BFS : public Searcher<Type, SearchType, Solution> {
    /**
     * search by bfs algorithm
     * @param searchable
     * @param start
     * @param end
     * @return
     */
    virtual Solution search(ISearchable<Type, SearchType>* searchable,
                            SearchNode<Type>* start, SearchNode<Type>* end) {


        queue<SearchNode<Type>*> queue;

        queue.push(start);

        this->countDiscovered = 0;

        SearchNode<Type>* current;
        bool found = false;

        //check founf or empty queue
        while(!queue.empty() && !found) {

            current = queue.front();
            queue.pop();

            if(!current->isVisited()) {
                current->visit();
                this->countDiscovered++;
            }

            if (current == end) {
                found = true;
                break;
            }

            vector<SearchNode<Type> *> *neighbours = searchable->getNeighbours(current);

            //go over ajeces
            for (SearchNode<Type> *adj:(*neighbours)) {
/*
                if (adj == end) {
                    found = true;
                    adj->parent = current;
                    break;
                }
                */
                if(!adj->isVisited()) {
                    adj->visit();
                    this->countDiscovered++;
                }

                if (!adj->isDicovered()) {
                    adj->setAsDiscovered();
                    queue.push(adj);
                    adj->parent = (current);
                }

            }

        }

        while (!queue.empty()) {
            queue.pop();
        }

        return this->getPathStr(start, end);

    }


};

#endif //HNJ_2NDROAD_BFS_H
