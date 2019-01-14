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

};

#endif //HNJ_2NDROAD_SEARCHER_H
