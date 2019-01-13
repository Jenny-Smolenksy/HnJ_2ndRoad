//
// Created by hilla on 1/8/19.
//

#ifndef HNJ_2NDROAD_UTILS_H
#define HNJ_2NDROAD_UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils {
public:
    static vector<string> split(string info,char c);

    static vector<string> splitbyEndl(string info);

};


#endif //HNJ_2NDROAD_UTILS_H
