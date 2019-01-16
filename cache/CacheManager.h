#include <utility>


#ifndef HNJ_2NDROAD_CACHMANAGER_H
#define HNJ_2NDROAD_CACHMANAGER_H

#include "string"
#include "FileToucher.h"

using namespace std;

class CacheManager {


public:

    virtual bool isSolution(string problem) {

        try {
            getSolution(std::move(problem));
            return true;
        }
        catch (...) {
            return false;
        }

    }

    virtual string getSolution(string problem) {}

    virtual void saveSolution(string problem, string solution) {}

};

#endif