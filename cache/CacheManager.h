
template <class Problem, class Solution>
class CacheManager {

public:

    virtual bool isSolution(Problem problem);

    virtual Solution getSolution(Problem problem);

    virtual void saveSolution(Problem problem, Solution solution);
};