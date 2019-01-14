//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_ISEARCHABLE_H
#define HNJ_2NDROAD_ISEARCHABLE_H

#include <termio.h>
#include <vector>
#include "SearchNode.h"

template<class Type, class SearchType>
class ISearchable {
public:
    virtual SearchNode<Type> *get(SearchType searchFor) = 0;


    virtual vector<SearchNode<Type> *> *getNeighbours(SearchNode<Type> *searchFor) = 0;

};

#endif //HNJ_2NDROAD_ISEARCHABLE_H
