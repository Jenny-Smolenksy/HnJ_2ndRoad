
#include "string"
#include "FileToucher.h"

using namespace std;

class CacheManager {


public:

    virtual bool isSolution(string problem) {

        try {
            getSolution(problem);
            return true;
        }
        catch (...) {
            return false;
        }

    }

    virtual string getSolution(string problem) {}

    virtual void saveSolution(string problem, string solution) {}
};