//
// Created by Win10Pro on 5/3/2021.
//

#ifndef LAB9_JOHNSONALOGRITHM__DIJKSTRANODE_H
#define LAB9_JOHNSONALOGRITHM__DIJKSTRANODE_H

#include <iostream>

class DijkstraNode {

public:
    int index;
    int cost;

    DijkstraNode(){

    }
    DijkstraNode(int index, int cost){
        this->index = index;
        this->cost = cost;
    }

    ~DijkstraNode() = default;
};

bool operator > (DijkstraNode node1, DijkstraNode node2);
bool operator < (DijkstraNode node1, DijkstraNode node2);
bool operator == (DijkstraNode node1, DijkstraNode node2);
bool operator <= (DijkstraNode node1, DijkstraNode node2);
bool operator >= (DijkstraNode node1, DijkstraNode node2);
std::ostream & operator << (std::ostream &out, DijkstraNode node);

#endif //LAB9_JOHNSONALOGRITHM__DIJKSTRANODE_H
