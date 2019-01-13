//
// Created by jenny on 1/12/19.
//

#ifndef HNJ_2NDROAD_SEARCHER_H
#define HNJ_2NDROAD_SEARCHER_H

#include "ISearcher.h"


template <class Problem, class Solution, class Value, class SearchType>
class Searcher : public ISearcher<Problem, Solution, Value, SearchType>{

    Solution search(ISearchable<Value, SearchType> , Problem problem);

};

#endif //HNJ_2NDROAD_SEARCHER_H
