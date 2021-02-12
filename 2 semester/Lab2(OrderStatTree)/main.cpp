#include <vector>
#include "Tree.h"


int main() {

   Tree<int>* tree = new Tree<int>;

   int ar[10] = { 7, 5, 3, 6, 8, 4, 9, 1, 2, 10};

   for(int i = 0; i < 10; i++){

       tree->insert(ar[i]);


   }

    std::cout << "size = "<< tree->size << "\n";
    tree->print();

}
