
#ifndef HNJ_2NDROAD_SOLVER_H
#define HNJ_2NDROAD_SOLVER_H

template<class Problem, class Solution>
class Solver {

public:

    virtual Solution solve(Problem problem) = 0;
};

#endif