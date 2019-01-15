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
        if (current != start) {
            return -1;
        }
        return cost;
    }

    virtual string getPathStr(SearchNode<Type>* start, SearchNode<Type>* end) {

        string str = "";

        SearchNode<Type>* current = end;

        str = current->parent->getDicrection(current);
        current = current->parent;
        while(current != start && current != nullptr) {

            str = current->parent->getDicrection(current)+ ", " + str;
            current = current->parent;
        }
        if (current != start) {
            return "no path";
        }
        return str;
    }

    virtual int getPathNodeAmount(SearchNode<Type>* start, SearchNode<Type>* end) {

        int count = 0;

        SearchNode<Type>* current = end;
        while(current != start && current != nullptr) {

            count++;
            current = current->parent;
        }
        if (current != start) {
            return -1;
        }
        return count;
    }



};

#endif //HNJ_2NDROAD_SEARCHER_H
