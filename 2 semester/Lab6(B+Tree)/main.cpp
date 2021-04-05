#include "BplusTree.h"

int main() {
    auto* tree = new BplusTree<int, int>(2);
    int ar[10] = { 4, 2, 3, 6, 5, 1, 8, 7, 9, 11};

    for(int i : ar){

        tree->insert(i, 0);
        std::cout << "------------insert---------" << std::endl;
        tree->print();

    }

    tree->insert(10, 5);
    std::cout << "------------insert---------" << std::endl;
    tree->print();

    std::cout << "search by key 10 " << tree->search(10) << "\n";
    std::cout << "search by key 3 " << tree->search(3) << "\n";

    for(int i = 1; i <= 11; i++){

        tree->erase(i);
        std::cout << "------------delete---------" << std::endl;
        tree->print();

    }

}
