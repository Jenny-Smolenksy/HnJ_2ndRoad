//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_DFS_H
#define HNJ_2NDROAD_DFS_H


#include <stack>
#include "Searcher.h"
#include "MatrixSearchProblem.h"

template <class Type, class SearchType, class Solution>
class DFS : public Searcher <Type, SearchType, Solution>{

public:

    virtual Solution search(ISearchable<Type, SearchType>* searchable,
                            SearchNode<Type>* start, SearchNode<Type>* end) {

        std::stack<SearchNode<Type>*> stack;
        stack.push(start);
        SearchNode<Type>* current;
        bool found = false;

        while(!stack.empty() && !found) {
            current = stack.top();
            stack.pop();

            if (current == end) {
                found = true;
                break;
            }


            if (!current->discovered) {
                current->discovered = true;

                vector<SearchNode<Type> *> *neighbours = searchable->getNeighbours(current);

                for (SearchNode<Type> *adj:(*neighbours)) {

                    if (adj == end) {
                        found = true;
                        adj->parent = current;
                        break;
                    }
                    if (!adj->discovered) {
                        stack.push(adj);
                        adj->parent = current;
                    }


                }

            }

        }

        while (!stack.empty()) {
            stack.pop();
        }


        return this->getPathStr(start, end);
    }



};



#endif //HNJ_2NDROAD_DFS_H
