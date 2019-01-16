//
// Created by hilla on 1/10/19.
//

#ifndef HNJ_2NDROAD_STRINGREVRSER_H
#define HNJ_2NDROAD_STRINGREVRSER_H

#include "string"
#include "Solver.h"


using namespace std;

class StringReverser : public Solver<string, string> {
public:
    /**
     * solve, reverse given string
     * @param p
     * @return
     */
    string solve(string p) override {
        string result;
        for (auto c : p) {
            result = c + result;
        }
        return result;
    }

};


#endif //HNJ_2NDROAD_STRINGREVRSER_H
