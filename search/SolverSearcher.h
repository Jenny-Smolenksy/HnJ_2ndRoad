//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_SOLVERSEARCHER_H
#define HNJ_2NDROAD_SOLVERSEARCHER_H

#include "../problem_solve/Solver.h"
#include "ISearchable.h"
#include "ISearcher.h"

template <class Problem, class Solution>
class SolverSearcher : public Solver<Problem, Solution> {

    ISearchable searchable;
    ISearcher searcher;


};


#endif //HNJ_2NDROAD_SOLVERSEARCHER_H
