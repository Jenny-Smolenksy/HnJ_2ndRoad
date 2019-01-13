//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_ISEARCHER_H
#define HNJ_2NDROAD_ISEARCHER_H

#include "ISearchable.h"

template <class Problem, class Solution, class Value, class SearchType>
class ISearcher {

    Solution search(ISearchable<Value, SearchType> , Problem problem);

};

#endif //HNJ_2NDROAD_ISEARCHER_H
