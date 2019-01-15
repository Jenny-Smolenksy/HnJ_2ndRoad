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

    bool discovered = false;
    Type value;
    double cost;

public:

    SearchNode *parent;
    SearchNode *up;
    SearchNode *down;
    SearchNode *right;
    SearchNode *left;

    SearchNode<Type>(){
        this->discovered = false;
    }

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

    void setAsDiscovered() {
        this->discovered = true;
    }

    bool isDicovered() {
        return this->discovered;
    }

    bool isUp() {
        return (this->up == nullptr);
    }

    bool isDown() {
        return (this->down == nullptr);
    }

    bool isRight() {
        return (this->right == nullptr);
    }

    bool isLeft() {
        return (this->left == nullptr);
    }

    void setValue(Type value){
        this->value = value;
    }

    Type getValue(){
        return this->value;
    }

    void setCost(double cost){
        this->cost = cost;
    }

    double getCost(){
        return this->cost;
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
