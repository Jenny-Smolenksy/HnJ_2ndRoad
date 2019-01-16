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
    /**
     * split string according to specific char
     * @param info
     * @param c
     * @return
     */
    static vector<string> split(string info,char c);

    /**
     * split string to lines
     * @param info
     * @return
     */
    static vector<string> splitbyEndl(string info);

};


#endif //HNJ_2NDROAD_UTILS_H
