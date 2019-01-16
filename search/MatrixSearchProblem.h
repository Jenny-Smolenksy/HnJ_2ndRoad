#include <utility>


#ifndef HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
#define HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H

#include "Matrix.h"

#define DIVIDER "*"

struct START_END_POINT {
    POINT start;
    POINT endp;
};
/**
 * matrix search problem class
 */
class MatrixSearchProblem {

    ISearchable<int, POINT> *matrix;
    START_END_POINT startEndPoint;

public:
    MatrixSearchProblem() = default;

    /**
     * get matrix problem
     * @return
     */
    ISearchable<int, POINT> *getMatrix() {
        return matrix;
    }

    /**
     * set matrix
     * @param mat
     */
    void setMatrix(ISearchable<int, POINT> *mat) {
        mat->assignFriends();
        matrix = mat;

    }

    /**
     * set start end
     * @param src
     * @param dst
     */
    void setStartEnd(POINT src, POINT dst){
        startEndPoint.start = src;
        startEndPoint.endp = dst;
    }

    /**
     * get start point
     * @return
     */
    POINT getStartPoint() {
        return startEndPoint.start;
    }

    /**
     * get end point
     * @return
     */
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
        string mat = matrix->search_base_to_string();

        finalProb += mat;
        finalProb += DIVIDER;

        finalProb += startEndPoint.start.pointToString();
        finalProb += DIVIDER;

        finalProb += startEndPoint.endp.pointToString();

        return finalProb;
    }


};

#endif //HNJ_2NDROAD_MATRIXSEARCHPROBLEM_H
