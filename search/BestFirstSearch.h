//
// Created by hilla on 1/14/19.
//

#ifndef HNJ_2NDROAD_BESTFIRSTSEARCH_H
#define HNJ_2NDROAD_BESTFIRSTSEARCH_H


#include "ISearcher.h"
#include "Searcher.h"
#include "queue"
#include <string>

template<class Type>
class Compare {
public:
    bool operator()(SearchNode<Type> *a, SearchNode<Type> *b) {
        return a->getCost() > b->getCost();
    }
};

template<class Type, class SearchType, class Solution>
class BestFirstSearch : public Searcher<Type, SearchType, Solution> {
    virtual Solution

    search(ISearchable<Type, SearchType> *searchable, SearchNode<Type> *start, SearchNode<Type> *endNode) {

        priority_queue < SearchNode<Type> * , vector<SearchNode<Type> *>, Compare<Type>>
        priority_queue1;

        priority_queue1.push(start);
        this->countDiscovered = 0;

        SearchNode<Type> *current;

        bool found = false;

        while (!priority_queue1.empty() && !found) {
            current = priority_queue1.top();
            priority_queue1.pop();

            this->updateCount(current);
            if (current == endNode) {
                //found the wanted node
                break;
            }
            vector<SearchNode<Type> *> *neighbours = searchable->getNeighbours(current);

            for (SearchNode<Type> *adj:(*neighbours)) {
                this->updateCount(adj);
                if (adj->parent == nullptr) {
                    adj->parent = current;
                    priority_queue1.push(adj);
                }
                if (adj == endNode) {
                    found = true;
                    adj->parent = (current);
                    break;
                }
            }
        }
        return this->getPathStr(start, endNode);
    }




};


#endif //HNJ_2NDROAD_BESTFIRSTSEARCH_H
