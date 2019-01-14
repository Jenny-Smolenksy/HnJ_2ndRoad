
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
        return &matrix[searchFor.y][searchFor.x];
    }

    virtual vector<SearchNode<int> *> *getNeighbours(SearchNode<int> *searchFor) {
        return searchFor->getFriends();

    }

    SearchNode<int> createNode(int *x) {
        SearchNode<int> nodeMatrix;
        nodeMatrix.value = x;
        nodeMatrix.cameFromFirection = UP;
        nodeMatrix.parent = NULL;
        nodeMatrix.up = nullptr;
        nodeMatrix.left = nullptr;
        nodeMatrix.right = nullptr;
        nodeMatrix.down = nullptr;
        return nodeMatrix;

    }

    void assignFriends() {
        POINT p;
        p.x = 0;
        p.y = 0;
        for (vector<SearchNode<int>> v: matrix){
            
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





