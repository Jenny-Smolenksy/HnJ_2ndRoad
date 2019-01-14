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
    Type *value;
    double cost;
    SearchNode *parent;
    SearchNode *up;
    SearchNode *down;
    SearchNode *right;
    SearchNode *left;
    DIRECTION cameFromFirection;


    vector<SearchNode<Type> *> *getFriends() {
        auto *friends = new vector<SearchNode<Type> *>();
        friends->insert(up);
        friends->insert(down);
        friends->insert(right);
        friends->insert(left);
        return friends;

    }

    void setValue(Type *value) {
         this->value = value;
    }

    Type* getValue() {
        return this->value;
    }

    void setCost(double cost) {
        this->cost = cost;
    }

    double getCost() {
        return this->cost;
    }

    SearchNode* getParent() {
        return this->parent;
    }
    void setParent(SearchNode* parent) {
        this->parent = parent;
    }
    SearchNode* getRight() {
        return this->right;
    }
    void setRight(SearchNode* right) {
        this->right = right;
    }
    SearchNode* getLeft() {
        return this->left;
    }
    void setLeft(SearchNode* left) {
        this->left = left;
    }
    SearchNode* getUp() {
        return this->up;
    }
    void setUP(SearchNode* up) {
        this->up = up;
    }
    SearchNode* getDown() {
        return this->down;
    }
    void setDown(SearchNode* down) {
        this->down = down;
    }
    SearchNode* getDirection() {
        return this->down;
    }
    void setDirection(DIRECTION direction) {
        this->cameFromFirection = direction;
    }



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
