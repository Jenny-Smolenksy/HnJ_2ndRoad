//
// Created by jenny on 1/12/19.
//

#ifndef HNJ_2NDROAD_SEARCHER_H
#define HNJ_2NDROAD_SEARCHER_H

#include "ISearcher.h"

#include <iostream>

template<class Type, class SearchType, class Solution>
class Searcher : public ISearcher<Type, SearchType, Solution> {


protected:
    int countDiscovered{};

public:

    virtual Solution search(ISearchable<Type, SearchType> *searchable,
                            SearchNode<Type> *start, SearchNode<Type> *end) = 0;

    /**
     * get path cost
     * @param start
     * @param end
     * @return
     */
    virtual double getPathCost(SearchNode<Type> *start, SearchNode<Type> *end) {

        double cost = 0;

        SearchNode<Type> *current = end;
        while (current != start && current != nullptr) {

            cost += current->getCost();
            current = current->parent;
        }

        if (current != start) {
            return -1;
        }
        cost += current->getCost();
        return cost;
    }

    /**
     * get the path as a string
     * @param start
     * @param end
     * @return
     */
    virtual string getPathStr(SearchNode<Type> *start, SearchNode<Type> *end) {

        string str;
        string str1;
        if (end->parent == NULL) {
            return "no path";
        }
        SearchNode<Type> *current = end;


        str1 = std::to_string(current->getValue());
        str = current->parent->getDicrection(current);
        current = current->parent;
        while (current != start && current != nullptr) {

            str = current->parent->getDicrection(current) + ", " + str;

            str1 = std::to_string(current->getValue()) + " -> " + str1;
            current = current->parent;
        }
        if (current != start) {
            return "no path";
        }
        str1 = std::to_string(current->getValue()) + " -> " + str1;
        cout << str1 << endl;
        return str;
    }

    /**
     * get the number of nudes involved in the final path
     * @param start
     * @param endNode
     * @return
     */
    virtual int getPathNodeAmount(SearchNode<Type> *start, SearchNode<Type> *endNode) {

        int count = 1;

        SearchNode<Type> *current = endNode;
        while (current != start && current != nullptr) {

            count++;
            current = current->parent;
        }
        if (current != start) {
            return -1;
        }
        return count;
    }

    /**
     * update the count of discoverd nodes
     * @param current
     */
    void updateCount(SearchNode<Type> *current) {
        if (!current->isDicovered()) {
            current->setAsDiscovered();
            this->countDiscovered++;
        }
    }

    /**
     * get all discoved nodes
     * @return
     */
    int getDiscovered() {
        return this->countDiscovered;
    }


};

#endif //HNJ_2NDROAD_SEARCHER_H
