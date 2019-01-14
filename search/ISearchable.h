//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_ISEARCHABLE_H
#define HNJ_2NDROAD_ISEARCHABLE_H

#include <termio.h>
#include <vector>
#include "SearchNode.h"

template<class Value, class SearchType>
class ISearchable {
public:
    virtual Value *get(SearchType searchFor) = 0;


    virtual vector <Value*> *getNeighbours(Value* searchFor) = 0;

};

#endif //HNJ_2NDROAD_ISEARCHABLE_H
