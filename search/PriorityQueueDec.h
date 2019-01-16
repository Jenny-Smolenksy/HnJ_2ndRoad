//
// Created by hilla on 1/16/19.
//

#ifndef HNJ_2NDROAD_PRIORITYQUEUEDEC_H
#define HNJ_2NDROAD_PRIORITYQUEUEDEC_H

#include "queue"
#include <string>
#include <vector>

using namespace std;

/**
 * wrapper for the built in priority queue. enables to send priority as parameter
 */
template<typename T, typename priority_tipe>
struct PriorityQueueDec {

    typedef pair<priority_tipe, T> PQElement;
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_tipe priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};




#endif //HNJ_2NDROAD_PRIORITYQUEUEDEC_H
