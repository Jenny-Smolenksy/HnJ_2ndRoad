//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_STATE_H
#define HNJ_2NDROAD_STATE_H

template <class Type>
class SearchNode {

    Type* value;
    double cost;
    Type* cameFrom;
};

enum DIRECTION { UP, DOWN, RIGHT, LEFT};

template <class Type>
class SearchNodeMatrix : public SearchNode<Type> {

    DIRECTION cameFromFirection;

};


#endif //HNJ_2NDROAD_STATE_H
