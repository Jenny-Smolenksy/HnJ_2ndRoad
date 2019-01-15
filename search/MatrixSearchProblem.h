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

    Matrix matrix;
    START_END_POINT startEndPoint;

public:
    MatrixSearchProblem(Matrix matrix1, POINT src, POINT dst) {
        matrix = std::move(matrix1);
        matrix1.assignFriends();
        startEndPoint.start = src;
        startEndPoint.endp = dst;
    }

    Matrix getMatrix() {
        return matrix;
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
        string mat = matrix.matToString();

        finalProb += mat;
        finalProb += DIVIDER;

        finalProb += startEndPoint.start.pointToString();
        finalProb += DIVIDER;

        finalProb += startEndPoint.endp.pointToString();

        return finalProb;
    }


};

#endif //HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
