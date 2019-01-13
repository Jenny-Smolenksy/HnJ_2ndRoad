


#include "ISearchable.h"
#include "MatrixSearchProblem.h"
#include "vector"
#include "../Utils.h"


struct POINT {
    int x;
    int y;
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

    virtual int get(POINT searchFor) {
        if (matrix.empty() || colNum < searchFor.x || matrix.size() < searchFor.y) {
            //matrix is empty || in valid request ||
            return -1;
        }
        return matrix[searchFor.y][searchFor.x];
    }



};



