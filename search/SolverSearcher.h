//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_SOLVERSEARCHER_H
#define HNJ_2NDROAD_SOLVERSEARCHER_H

#include <string>
#include "../problem_solve/Solver.h"
#include "ISearchable.h"
#include "ISearcher.h"
#include "Matrix.h"
#include "MatrixSearchProblem.h"
#include "string.h"
template <class Type>
class SolverSearcher : public Solver<MatrixSearchProblem<Type>, std::string > {

    ISearcher<START_END_POINT, std::string, Type, POINT> searcher;

    virtual std::string solve(MatrixSearchProblem<Type> problem) {
        return searcher.search(problem.matrix, problem.startEndPoint);
    }
};


#endif //HNJ_2NDROAD_SOLVERSEARCHER_H
