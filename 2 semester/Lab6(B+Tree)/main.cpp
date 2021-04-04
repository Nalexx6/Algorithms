#include "BplusTree.h"

int main() {
    auto* tree = new BplusTree<int, int>(2);
    int ar[11] = { 4, 2, 3, 6, 5, 1, 8, 7, 9, 10, 11};

    for(int i = 0; i < 11; i++){

        tree->insert(ar[i], 0);
        std::cout << "------------insert---------\n";
        tree->print();

    }

}
