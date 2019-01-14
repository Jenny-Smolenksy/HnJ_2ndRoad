//
// Created by hilla on 1/14/19.
//

#ifndef HNJ_2NDROAD_BESTFIRSTSEARCH_H
#define HNJ_2NDROAD_BESTFIRSTSEARCH_H


#include "ISearcher.h"
#include "PriorityQueue.h"
#include "Matrix.h"
#include <string>

using namespace std;
struct Node {
    int value;
    int prior;
    Node *parent;

};
struct SearchResult {
    int developedNodes;
    int totalWeight;
    string path;
};

class Compare {
    bool operator()(Node *a, Node *b) {
        return a->value > b->value;
    }
};

template<class Problem, class Solution, class Value, class SearchType>
class BestFirstSearch : public ISearcher<Problem, Solution, Value, SearchType> {
/*
    Solution search(ISearchable<Value, SearchType> searchable, Problem p) override {
        PriorityQueue priorityQueue;
        SearchResult searchResult;

        searchResult.developedVerticels = 0;
        searchResult.shortestPathRoute = "";
        searchResult.shortestPathWeight = 0;
        State* goalState;
        goalState = searchable->getGoalState();

        priority_queue<Node *, std::vector<Node *>, Compare> pqu;

        searchable->getInitialState()->commingFrom = Start;

        pqu.push((searchable->getInitialState()));

        State *current_node;
        while (!pqu.empty())
        {
            current_node = pqu.top();
            pqu.pop();

            if (current_node == goalState) //finished
            {
                break;
            }



            //top
            if (current_node->top != NULL && !current_node->top->isInfinity && current_node->top->commingFrom == NotSet)
            {
                current_node->top->commingFrom = Down;
                pqu.push(current_node->top);

            }

            //bottom
            if (current_node->bottom != NULL && !current_node->bottom->isInfinity && current_node->bottom->commingFrom == NotSet)
            {
                current_node->bottom->commingFrom = Up;
                pqu.push(current_node->bottom);
            }
            //left
            if (current_node->left != NULL && !current_node->left->isInfinity && current_node->left->commingFrom == NotSet)
            {
                current_node->left->commingFrom = Right;
                pqu.push(current_node->left);
            }
            //right
            if (current_node->right != NULL && !current_node->right->isInfinity && current_node->right->commingFrom == NotSet)
            {
                current_node->right->commingFrom = Left;
                pqu.push(current_node->right);
            }

            searchResult.developedVerticels++;

        }

        //no path exists!
        if (current_node != goalState){
            searchResult.shortestPathRoute = "";
            searchResult.shortestPathWeight = -1;
            return searchResult;
        }


        bool arrivedStart = false;

        string currentDir;
        while (!arrivedStart)
        {

            searchResult.shortestPathWeight += current_node->weigth;
            switch (current_node->commingFrom)
            {
                case Up:
                    current_node = current_node->top;
                    currentDir = "Down, ";
                    break;
                case Down:
                    current_node = current_node->bottom;
                    currentDir = "Up, ";
                    break;
                case Left:
                    current_node = current_node->left;
                    currentDir = "Right, ";
                    break;
                case Right:
                    current_node = current_node->right;
                    currentDir = "Left, ";
                    break;
                case Start:
                    arrivedStart = true;
                    break;
                default:
                    throw "not valid scenario";
            }
            if (!arrivedStart)
                searchResult.shortestPathRoute.insert(0, currentDir);
        }
        searchResult.shortestPathRoute =
                searchResult.shortestPathRoute.substr(0, searchResult.shortestPathRoute.length() - 2);


        return searchResult;


    }
*/
};


#endif //HNJ_2NDROAD_BESTFIRSTSEARCH_H
