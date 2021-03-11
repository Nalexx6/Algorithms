#include <iostream>
#include "OptimalBST.h"
int main() {

    std::vector<int> elements = {1, 2, 3, 4, 5};
    std::vector<double> probs =  {0.15, 0.1, 0.05, 0.1, 0.2};
    std::vector<double> fictProbs = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};

    OptimalBST<int>* tree = new OptimalBST(elements, probs, fictProbs);

    tree->print();
}
