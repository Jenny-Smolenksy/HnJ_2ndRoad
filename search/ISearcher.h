//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_ISEARCHER_H
#define HNJ_2NDROAD_ISEARCHER_H

#include "ISearchable.h"

template <class Type, class SearchType, class Solution>
class ISearcher {

public:
    virtual Solution search(ISearchable<Type, SearchType>* searchable,
            SearchNode<Type>* start, SearchNode<Type>* end) = 0;

};

#endif //HNJ_2NDROAD_ISEARCHER_H
