//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_STATE_H
#define HNJ_2NDROAD_STATE_H
#define COMMA ","

#include <string>
#include "vector"

using namespace std;

/**
 * searchNode class
 * @tparam Type
 */
template<class Type>
class SearchNode {

    bool discovered = false;
    Type value;
    double cost{};
    bool visited{};

public:

    SearchNode *parent;
    SearchNode *up;
    SearchNode *down;
    SearchNode *right;
    SearchNode *left;

    /**
     * constructor
     */
    SearchNode<Type>(){
        this->discovered = false;
        this->visited = false;
    }

    /**
     * get direction
     * @param searchNode
     * @return
     */
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

    /**
     * set As Discovered
     */
    void setAsDiscovered() {
        this->discovered = true;
    }

    /**
     * check if Discovered
     */
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

    /**
     * set value
     * @param value
     */
    void setValue(Type value){
        this->value = value;
    }

    /**
     * get value
     * @return
     */
    Type getValue(){
        return this->value;
    }

    /**
     * set cost
     * @param cost
     */
    void setCost(double cost){
        this->cost = cost;
    }

    /**
     * get cost
     * @return
     */
    double getCost(){
        return this->cost;
    }

    /**
     * check if visitied
     * @return
     */
    bool isVisited() {
        return this->visited;
    }

    /**
     * visit
     */
    void visit() {
        this->visited = true;
    }

    /**
     * initial a node
     */
    void inital(){
        this->discovered = false;
        this->visited = false;
        this->parent= nullptr;
    }


};
/**
 * point class
 */
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
