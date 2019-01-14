


#include "ISearchable.h"
#include "MatrixSearchProblem.h"
#include "vector"
#include "../Utils.h"


#define ENDLINE "|"


class Matrix : public ISearchable<int, POINT> {
    vector<vector<SearchNode<int>>> matrix;
    int colNum;

public:
    Matrix() {
        colNum = 0;

    }

    void addRow(string row) {
        if (!row.empty()) {
            vector<SearchNode<int>> realRow = createRow(Utils::split(row, ','));
            colNum = (int) realRow.size();
            matrix.push_back(realRow);
        }
    }

    vector<SearchNode<int >> createRow(vector<string> row) {
        vector<SearchNode<int>> result;
        for (string value:row) {
            int x = atoi(value.data());
            SearchNode<int> node = createNode(&x);
            result.push_back(node);
        }
        return result;
    }

    virtual SearchNode<int> *get(POINT searchFor) {
        if (matrix.empty() || colNum < searchFor.x || matrix.size() < searchFor.y) {
            //matrix is empty || in valid request ||
            return nullptr;
        }
        if (*(matrix[searchFor.y][searchFor.x].value) == -1) {
            return nullptr;
        }
        return &matrix[searchFor.y][searchFor.x];
    }

    virtual vector<SearchNode<int> *> *getNeighbours(SearchNode<int> *searchFor) {
        auto *friends = new vector<SearchNode<int> *>();

        //assign friends (real) the direction they were reached from
        if (searchFor->right != nullptr) {
            searchFor->right->cameFromFirection = LEFT;
            friends->push_back(searchFor->right);
        }
        if (searchFor->left != nullptr) {
            searchFor->left->cameFromFirection = RIGHT;
            friends->push_back(searchFor->left);
        }
        if (searchFor->up != nullptr) {
            searchFor->up->cameFromFirection = DOWN;
            friends->push_back(searchFor->up);
        }
        if (searchFor->down != nullptr) {
            searchFor->down->cameFromFirection = UP;
            friends->push_back(searchFor->down);
        }

        //assign parent situation
        for (SearchNode<int> *node:*friends) {
            node->parent = searchFor;
        }
        return friends;

    }

    SearchNode<int> createNode(int *x) {
        SearchNode<int> nodeMatrix;
        nodeMatrix.value = x;
        nodeMatrix.cost = *x;
        nodeMatrix.cameFromFirection = UP;
        nodeMatrix.parent = NULL;
        nodeMatrix.up = nullptr;
        nodeMatrix.left = nullptr;
        nodeMatrix.right = nullptr;
        nodeMatrix.down = nullptr;
        return nodeMatrix;

    }

    void assignFriends() {
        int y = 0;
        for (vector<SearchNode<int>> v: matrix) {
            int x = 0;
            for (SearchNode<int> node:v) {
                node.up = get(POINT(x, y - 1));
                node.down = get(POINT(x, y + 1));
                node.right = get(POINT(x + 1, y));
                node.left = get(POINT(x - 1, y));
                x++;
            }
            //move to other line
            y++;
        }
    }

    virtual string matToString() {
        string result;
        for (vector<SearchNode<int>> s:matrix) {
            for (SearchNode<int> c: s) {
                int val = *c.value;
                result += to_string(val);
                result += COMMA;
            }
            result += ENDLINE;
        }
        return result;
    }


};





