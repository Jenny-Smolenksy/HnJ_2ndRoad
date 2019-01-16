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

template<class Type>
class SolverSearcher : public Solver<MatrixSearchProblem, std::string> {

    ISearcher<Type, POINT, string> *searcher;
public:
    SolverSearcher(ISearcher<Type, POINT, string> *s) {
        searcher = s;
    }

    virtual std::string solve(MatrixSearchProblem problem) {

        SearchNode<Type> *startNode = problem.getMatrix()->get(problem.getStartPoint());
        SearchNode<Type> *endNode = problem.getMatrix()->get(problem.getEndPoint());

        return searcher->search(problem.getMatrix(), startNode, endNode);
    }

    ~SolverSearcher() {
        searcher = nullptr;
    }
};


#endif //HNJ_2NDROAD_SOLVERSEARCHER_H
