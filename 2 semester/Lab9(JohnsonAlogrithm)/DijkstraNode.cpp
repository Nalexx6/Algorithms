//
// Created by Win10Pro on 5/3/2021.
//

#include "DijkstraNode.h"


bool operator > (DijkstraNode node1, DijkstraNode node2) {
    return node1.cost > node2.cost;
}

bool operator < (DijkstraNode node1, DijkstraNode node2) {
    return node1.cost < node2.cost;
}

bool operator == (DijkstraNode node1, DijkstraNode node2) {
    return node1.cost == node2.cost && node1.index == node2.index;
}

bool operator<=(DijkstraNode node1, DijkstraNode node2) {
    return node1.cost <= node2.cost;
}

bool operator>=(DijkstraNode node1, DijkstraNode node2) {
    return node1.cost >= node2.cost;
}

std::ostream &operator<<(std::ostream &out, DijkstraNode node) {
    out << "index: " << node.index << " cost: " << node.cost;
    return out;
}
