//
// Created by jenny on 1/12/19.
//

#ifndef HNJ_2NDROAD_SEARCHER_H
#define HNJ_2NDROAD_SEARCHER_H

#include "ISearcher.h"

template <class Type, class SearchType, class Solution>
class Searcher : public ISearcher<Type, SearchType, Solution>{

public:

    virtual Solution search(ISearchable<Type, SearchType>* searchable,
                            SearchNode<Type>* start, SearchNode<Type>* end) = 0;

    virtual double getPathCost(SearchNode<Type>* start, SearchNode<Type>* end) {

        double cost = 0;

        SearchNode<Type>* current = end;
        while(current != start && current != nullptr) {

            cost += current->cost;
            current = current->parent;
        }
        if(current != nullptr) {
            cost += current->cost;
        }
        return cost;
    }

    virtual string getPath(SearchNode<Type>* start, SearchNode<Type>* end) {

        string str = "";

        SearchNode<Type>* current = end;
        while(current != start && current != nullptr) {

            str = current->parent->getDicrection(current)+ ", " + str;
            current = current->parent;
        }
        return str;
    }



};

#endif //HNJ_2NDROAD_SEARCHER_H
