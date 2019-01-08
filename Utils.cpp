//
// Created by hilla on 1/8/19.
//

#include <sstream>
#include "Utils.h"

vector<string> Utils::split(string info, char c) {
    stringstream easy2split(info);
    string part;
    vector<string> allparts;

    while (getline(easy2split, part, c)) {
        allparts.push_back(part);
    }
    return allparts;
}
