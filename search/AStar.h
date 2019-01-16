//
// Created by hilla on 1/16/19.
//

#ifndef HNJ_2NDROAD_ASTAR_H
#define HNJ_2NDROAD_ASTAR_H

#include "ISearchable.h"
#include "Searcher.h"
#include<bits/stdc++.h>
#include "PriorityQueueDec.h"

using namespace std;


/**
 * A star alogirthem
 * @tparam Type
 * @tparam SearchType
 * @tparam Solution
 */
template<class Type, class SearchType, class Solution>
class AStar : public Searcher<Type, SearchType, Solution> {

    /**
     * the heuristic function
     * @param a
     * @param b
     * @param searchable
     * @return
     */
    inline int heuristic(SearchNode<Type> *a, SearchNode<Type> *b, ISearchable<Type, SearchType> *searchable) {
        POINT locA = searchable->getlocation(a);
        POINT locB = searchable->getlocation(b);
        return abs(locA.x - locB.x) + std::abs(((int) (locA.y - locB.y)));
    }

    /***
     * search
     * @param searchable
     * @param start
     * @param endNode
     * @return
     */
    virtual Solution search(ISearchable<Type, SearchType> *searchable, SearchNode<Type> *start, SearchNode<Type> *endNode) {

        map<SearchNode<Type> *, int> cost_so_far;
        this->countDiscovered = 0;

        PriorityQueueDec<SearchNode<Type> *, int> frontier;
        frontier.put(start, 0);

        cost_so_far[start] = 0;

        SearchNode<Type> *current;
        /*while there are items to check */
        while (!frontier.empty()) {

            current = frontier.get();
            this->updateCount(current);
            if (current == endNode) {
                break;
            }

            vector<SearchNode<Type> *> *neighbours = searchable->getNeighbours(current);
            /*iterete threw all the neigbours*/
            for (SearchNode<Type> *adj : (*neighbours)) {
                int newCost = cost_so_far[current] + (int) adj->getCost();
                if (cost_so_far.find(adj) == cost_so_far.end() || newCost < cost_so_far[adj]) {
                    //only if u worth it
                    cost_so_far[adj] = newCost;
                    int priority = newCost + heuristic(adj, endNode, searchable);
                    frontier.put(adj, priority);
                    adj->parent = current;
                    this->updateCount(adj);
                }
            }

        }
        return this->getPathStr(start, endNode);
    }


};


#endif //HNJ_2NDROAD_ASTAR_H
