//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_ISEARCHABLE_H
#define HNJ_2NDROAD_ISEARCHABLE_H

#include <termio.h>

template <class Value, class SearchType>
class ISearchable {

    virtual Value get(SearchType searchFor) = 0;

};

#endif //HNJ_2NDROAD_ISEARCHABLE_H
