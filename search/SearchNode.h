//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_STATE_H
#define HNJ_2NDROAD_STATE_H
#define COMMA ","

#include <string>
#include "vector"

using namespace std;
enum DIRECTION {
    UP, DOWN, RIGHT, LEFT
};

template<class Type>
class SearchNode {
public:
    int cost{};
    SearchNode *parent;
    SearchNode *up;
    SearchNode *down;
    SearchNode *right;
    SearchNode *left;
    bool discovered = false;


    string getDicrection(SearchNode<Type>* searchNode) {

        if (this->up!= nullptr && this->up == searchNode) {
            return "UP";
        }
        if (this->down!= nullptr && this->down == searchNode) {
            return "DOWN";
        }
        if (this->right != nullptr && this->right == searchNode) {
            return "RIGHT";
        }
        if (this->left != nullptr && this->left == searchNode) {
            return "LEFT";
        }
        return "";
    }

};

class POINT {
public:
    int x;
    int y;

    POINT() = default;

    POINT(int a, int b) {
        x = a;
        y = b;

    }
    string pointToString() {
        string res;
        res += to_string(x);
        res += COMMA;
        res += to_string(y);
        return res;
    }

};


#endif //HNJ_2NDROAD_STATE_H
