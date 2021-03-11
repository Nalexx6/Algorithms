#include <iostream>
#include "SplayTree.h"

int main() {
    auto* tree = new SplayTree<int>;

    int ar[10] = { 7, 5, 3, 6, 8, 4, 9, 1, 2, 10};

    for(int & i : ar){

        tree->insert(i);
        std::cout << "------------insert---------" << std::endl;
        tree->print();


    }

    for(int i = 0; i < 5; i++){

        int k;
        std::cout << "Enter element to get\n";
        std::cin >> k;
        tree->get(k);
        tree->print();

    }

//    tree->print();
   for(int i = 1; i <= 10; i++){

       std::cout << "-------------------deleting------------\n";

       tree->erase(i);
       tree->print();
//       tree->print();

   }

}
