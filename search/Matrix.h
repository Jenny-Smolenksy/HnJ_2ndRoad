
#include "ISearchable.h"
#include "MatrixSearchProblem.h"
#include "vector"
#include "../Utils.h"


#define ENDLINE "|"


#ifndef HNJ_2NDROAD_MATRIX_H
#define HNJ_2NDROAD_MATRIX_H

class Matrix : public ISearchable<int, POINT> {
    vector<vector<SearchNode<int> *>> matrix;
    int colNum;
    vector<vector<SearchNode<int> *> *> destroy;


public:
    Matrix() {
        colNum = 0;
    }

    void addRow(string row) {
        if (!row.empty()) {
            auto *realRow = new vector<SearchNode<int> *>();
            createRow(Utils::split(row, ','), realRow);
            colNum = (int) realRow->size();
            matrix.push_back(*realRow);
            destroy.push_back(realRow);
        }
    }

    void createRow(vector<string> row, vector<SearchNode<int> *> *result) {
        for (const string &value:row) {
            int x = atoi(value.data());
            auto node = new SearchNode<int>();
            createNode(&x, node);
            result->push_back(node);
        }

    }

    virtual SearchNode<int> *get(POINT searchFor) {
        if (matrix.empty() || colNum - 1 < searchFor.y || matrix.size() - 1 < searchFor.x || searchFor.x < 0 ||
            searchFor.y < 0) {
            //matrix is empty || in valid request ||
            return nullptr;
        }
        if (matrix[searchFor.x][searchFor.y]->getCost() == -1) {
            return nullptr;
        }
        return matrix[searchFor.x][searchFor.y];
    }

    virtual vector<SearchNode<int> *> *getNeighbours(SearchNode<int> *searchFor) {
        auto *friends = new vector<SearchNode<int> *>();
        this->destroy.push_back(friends);
        //assign friends (real) the direction they were reached from
        if (searchFor->right != nullptr) {
            //  searchFor->right->cameFromFirection = RIGHT;
            friends->push_back(searchFor->right);
        }
        if (searchFor->left != nullptr) {
            //searchFor->left->cameFromFirection = LEFT;
            friends->push_back(searchFor->left);
        }
        if (searchFor->up != nullptr) {
            //searchFor->up->cameFromFirection = UP;
            friends->push_back(searchFor->up);
        }
        if (searchFor->down != nullptr) {
            //searchFor->down->cameFromFirection = DOWN;
            friends->push_back(searchFor->down);
        }
/*
        //assign parent situation
        for (SearchNode<int> *node:*friends) {
            node->parent = searchFor;
        }
        */
        return friends;

    }

    void createNode(int *x, SearchNode<int> *nodeMatrix) {
        nodeMatrix->setCost(*x);
        nodeMatrix->setValue(*x);
        nodeMatrix->parent = nullptr;
        nodeMatrix->down = nullptr;
        nodeMatrix->up = nullptr;
        nodeMatrix->left = nullptr;
        nodeMatrix->right = nullptr;

    }

    void assignFriends() {
        int y = 0;
        for (vector<SearchNode<int> *> v: matrix) {
            int x = 0;
            for (SearchNode<int> *node:v) {
                node->up = (get(POINT(y - 1, x)));
                node->down = (get(POINT(y + 1, x)));
                node->right = (get(POINT(y, x + 1)));
                node->left = (get(POINT(y, x - 1)));
                x++;
            }
            //move to other line
            y++;
        }
    }

    virtual string search_base_to_string() {
        string result;
        for (vector<SearchNode<int> *> s:matrix) {
            for (SearchNode<int> *c: s) {
                result += to_string(c->getValue());
                result += COMMA;
            }
            result.pop_back();
            result += ENDLINE;
        }
        return result;
    }

    void clear() {
        this->matrix.clear();
        this->colNum = 0;
    }

    bool empty() {
        return matrix.empty();
    }

    int size() {
        return colNum;
    }

    virtual POINT getlocation(SearchNode<int> *searchFor) {
        int i = 0;
        pair<bool, int> result;

        for (vector<SearchNode<int> *> row:matrix) {
            result = findInVector(&row, searchFor);
            if (result.first) {
                //found the right row, and position in it (col)
                return POINT(i, result.second);
            }

        }
        //not an item
        return POINT(-1, -1);

    }

    pair<bool, int> findInVector(vector<SearchNode<int> *> *row, SearchNode<int> *searchFor) {
        pair<bool, int> result;
        result.first = false;
        result.second = -1;
        int j = 0;
        // Find given element in vector
        for (SearchNode<int> *node:*row) {
            if (node == searchFor) {
                result.first = true;
                result.second = j;
                break;
            }
            j++;

        }
        return result;
    }

    ~Matrix() {
        for (vector<SearchNode<int> *> v: matrix) {
            for (SearchNode<int> *node:v) {
                delete node;
            }
            //move to other line

        }
        for (vector<SearchNode<int> *> *p:destroy) {
            delete p;
        }
    }


};


#endif
