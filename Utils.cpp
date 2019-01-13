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

vector<string> Utils::splitbyEndl(string info) {
    vector<string> strings;
    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = info.find("\n", prev)) != std::string::npos) {
        strings.push_back(info.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(info.substr(prev));
    if (strings.back().empty()) {
        strings.pop_back();
    }
    return strings;
}
