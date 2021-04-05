#include <iostream>
#include "OptimalBST.h"
int main() {

    std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7};
    std::vector<double> probs =  {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
    std::vector<double> fictProbs = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};

    auto* tree = new OptimalBST(elements, probs, fictProbs);

    tree->print();

}
