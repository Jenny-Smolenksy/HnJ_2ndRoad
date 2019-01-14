//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_STATE_H
#define HNJ_2NDROAD_STATE_H
#define COMMA ","

#include <string>

using namespace std;
enum DIRECTION {
    UP, DOWN, RIGHT, LEFT
};

template<class Type>
class SearchNode {
public:
    Type *value;
    double cost;
    SearchNode *parent;
    DIRECTION cameFromFirection;;
};

class POINT {
public:
    int x;
    int y;

    string pointToString() {
        string res;
        res += to_string(x);
        res += COMMA;
        res += to_string(y);
        return res;
    }


};


#endif //HNJ_2NDROAD_STATE_H
