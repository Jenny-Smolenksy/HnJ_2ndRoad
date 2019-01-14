//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_ISEARCHABLE_H
#define HNJ_2NDROAD_ISEARCHABLE_H

#include <termio.h>
#include "SearchNode.h"

template <class Value, class SearchType>
class ISearchable {

    virtual Value* get(SearchType searchFor) = 0;

    virtual SearchNode<Value>* getNode(SearchType searchFor);

    virtual SearchNode<Value>** getNeighbours(SearchType searchFor);

};

#endif //HNJ_2NDROAD_ISEARCHABLE_H
