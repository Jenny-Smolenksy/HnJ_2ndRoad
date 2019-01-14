//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_DFS_H
#define HNJ_2NDROAD_DFS_H

#include <queue>
#include <stack>
#include "Searcher.h"
#include "MatrixSearchProblem.h"

template <class Type, class SearchType, class Solution>
class DFS : public Searcher <Type, SearchType, Solution>{

    virtual Solution search(ISearchable<Type, SearchType>* searchable,
                            SearchNode<Type>* start, SearchNode<Type>* end) {

        std::stack<SearchNode<Type>> stack;
        stack.push(&start);
        SearchNode<Type>* current;

        while(!stack.empty()) {
            current = stack.pop();

            if(current == end) {
                break;
            }
            if(!current->discovered) {
                current->discovered = true;

                 vector<SearchNode<Type>*>* neighbours = searchable->getNeighbours(current);
                 for(SearchNode<Type>* adj:neighbours) {

                     if (adj == end) {
                         break;
                     }
                     stack.push(&adj);

                 }

            }
        }

        while(!stack.empty()) {
            stack.pop();
        }




        //problem of dfs dtart_end point
        //start point

        //push to stack
        //pop
        //get my neibous

    }



};



#endif //HNJ_2NDROAD_DFS_H
