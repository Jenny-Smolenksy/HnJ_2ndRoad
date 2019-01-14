


#include "ISearchable.h"
#include "MatrixSearchProblem.h"
#include "vector"
#include "../Utils.h"

#define COMMA ","
#define ENDLINE "|"
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


class Matrix : public ISearchable<int, POINT> {
    vector<vector<int>> matrix;
    int colNum;

public:
    Matrix() {
        colNum = 0;

    }

    void addRow(string row) {
        if (!row.empty()) {
            vector<int> realRow = createRow(Utils::split(row, ','));
            colNum = (int) realRow.size();
            matrix.push_back(realRow);
        }
    }

    vector<int> createRow(vector<string> row) {
        vector<int> result;
        for (string value:row) {
            int x = atoi(value.data());
            result.push_back(x);
        }
        return result;
    }

    virtual int *get(POINT searchFor) {
        if (matrix.empty() || colNum < searchFor.x || matrix.size() < searchFor.y) {
            //matrix is empty || in valid request ||
            return nullptr;
        }
        return &matrix[searchFor.y][searchFor.x];
    }

    virtual SearchNode<int >* getNode(POINT searchFor){}

    virtual SearchNode<int >** getNeighbours(POINT searchFor){}

    virtual string matToString() {
        string result;
        for (vector<int> s:matrix) {
            for (int c: s) {
                result += to_string(c);
                result += COMMA;
            }
            result += ENDLINE;
        }
        return result;
    }


};



