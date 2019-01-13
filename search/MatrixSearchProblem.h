
#ifndef HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
#define HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H

#include "Matrix.h"

struct START_END_POINT {
    POINT start;
    POINT end;
};
template<class Type>
class MatrixSearchProblem  {

    Matrix matrix;
    START_END_POINT startEndPoint;

};
#endif //HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
