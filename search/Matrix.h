//
// Created by jenny on 1/13/19.
//

#ifndef HNJ_2NDROAD_MATRUX_H
#define HNJ_2NDROAD_MATRUX_H

#include "ISearchable.h"
#include "MatrixSearchProblem.h"

struct POINT {
    int x;
    int y;
};


template <class Type>
class Matrix : public ISearchable<Type, POINT> {

public:

    virtual Type get(POINT searchFor) {}

};


#endif //HNJ_2NDROAD_MATRUX_H
