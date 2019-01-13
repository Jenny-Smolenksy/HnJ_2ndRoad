//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_SOLVERSEARCHER_H
#define HNJ_2NDROAD_SOLVERSEARCHER_H

#include "../problem_solve/Solver.h"
#include "ISearchable.h"
#include "ISearcher.h"
#include "Matrix.h"
#include "MatrixSearchProblem.h"

template <class Type, class Solution>
class SolverSearcher : public Solver<MatrixSearchProblem<Type>, Solution> {

    ISearchable searchable;
    ISearcher searcher;

};


#endif //HNJ_2NDROAD_SOLVERSEARCHER_H
