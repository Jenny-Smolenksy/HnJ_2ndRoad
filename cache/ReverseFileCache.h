#include "FileCacheManager.h"
#include "string"

using namespace std;

template<char *Problem, char *Soltion>
class ReverseFileCache : FileCacheManager {

    virtual char *getSolution(char *problem);

    virtual void saveSolution(char *problem, char *solution);

};


