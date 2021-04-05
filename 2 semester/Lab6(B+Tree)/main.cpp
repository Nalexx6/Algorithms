#include "BplusTree.h"

int main() {
    auto* tree = new BplusTree<int, int>(2);
    int ar[11] = { 4, 2, 3, 6, 5, 1, 8, 7, 9, 10, 11};

    for(int i : ar){

        tree->insert(i, 0);
        std::cout << "------------insert---------" << std::endl;
        tree->print();

    }

    for(int i = 1; i <= 11; i++){

        tree->erase(i);
        std::cout << "------------delete---------" << std::endl;
        tree->print();

    }

}
