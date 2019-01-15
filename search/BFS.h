//
// Created by jenny on 1/15/19.
//

#ifndef HNJ_2NDROAD_BFS_H
#define HNJ_2NDROAD_BFS_H

#include "Searcher.h"
#include <queue>

template <class Type, class SearchType, class Solution>
class BFS : public Searcher<Type, SearchType, Solution> {
    virtual Solution search(ISearchable<Type, SearchType>* searchable,
                            SearchNode<Type>* start, SearchNode<Type>* end) {

        queue<SearchNode<Type>*> queue;

        queue.push(start);

        SearchNode<Type>* current;
        bool found = false;

        while(!queue.empty() && !found) {
            current = queue.pop();

            if (current == end) {
                break;
            }

            if (!current->discovered) {
                current->discovered = true;

                vector<SearchNode<Type> *> *neighbours = searchable->getNeighbours(current);

                for (SearchNode<Type> *adj:(*neighbours)) {

                    if (adj == end) {
                        found = true;
                        adj->parent = current;
                        break;
                    }
                    if (!adj->discovered) {
                        queue.push(adj);
                        adj->parent = current;
                    }


                }

            }

        }

        while (!stack.empty()) {
            stack.pop();
        }

        return this->getPathStr(start, end);

    }


};

#endif //HNJ_2NDROAD_BFS_H
