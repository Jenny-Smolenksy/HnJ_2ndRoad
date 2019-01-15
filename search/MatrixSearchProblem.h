#include <utility>


#ifndef HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
#define HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H

#include "Matrix.h"

#define DIVIDER "*"

struct START_END_POINT {
    POINT start;
    POINT endp;
};

class MatrixSearchProblem {

    ISearchable<int, POINT> *matrix;
    START_END_POINT startEndPoint;

public:
    MatrixSearchProblem() = default;

    ISearchable<int, POINT> *getMatrix() {
        return matrix;
    }

    void setMatrix(ISearchable<int, POINT> *mat) {
        mat->assignFriends();
        matrix = mat;

    }

    void setStartEnd(POINT src, POINT dst){
        startEndPoint.start = src;
        startEndPoint.endp = dst;
    }

    POINT getStartPoint() {
        return startEndPoint.start;
    }

    POINT getEndPoint() {
        return startEndPoint.endp;
    }

    /**
     * string down the problem:
     * matrix$startpoint$end point
     * @return
     */
    string problemToString() {
        string finalProb;
        string mat = matrix->to_string();

        finalProb += mat;
        finalProb += DIVIDER;

        finalProb += startEndPoint.start.pointToString();
        finalProb += DIVIDER;

        finalProb += startEndPoint.endp.pointToString();

        return finalProb;
    }


};

#endif //HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
