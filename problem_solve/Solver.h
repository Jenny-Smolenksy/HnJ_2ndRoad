template<class Problem, class Solution>
class Solver {

public:

    virtual Solution solve(Problem problem) = 0;
};