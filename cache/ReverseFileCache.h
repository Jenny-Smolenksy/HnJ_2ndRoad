#include "FileCacheManager.h"

template <class Problem, class Solution>
class ReverseFileCache : FileCacheManager<Problem, Solution> {


    virtual bool isSolution(Problem problem);

    virtual Solution getSolution(Problem problem);

    virtual void saveSolution(Problem problem, Solution solution);

};