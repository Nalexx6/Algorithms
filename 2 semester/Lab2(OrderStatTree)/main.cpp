#include <vector>
#include "Tree.h"


int main() {

   Tree<int>* tree = new Tree<int>;

   int ar[10] = { 7, 5, 3, 6, 8, 4, 9, 1, 2, 10};

   for(int i = 0; i < 10; i++){

       tree->insert(ar[i]);
       std::cout << "------------insert---------\n";
       tree->print();


   }

   std::cout<<tree->getStat(10);

//   for(int i = 0; i < 10; i++){
//
//       std::cout << "-------------------deleting------------\n";
//
//       tree->erase(i);
//       tree->print();
////       tree->print();
//
//   }



//    std::cout << "-------------------deleting------------\n";
//
//    tree->erase(4);
//    tree->print();
//
//    std::cout << "-------------------deleting------------\n";
//
//    tree->erase(9);
//
//
//    std::cout << "-------------------deleting------------\n";
//
//    tree->erase(1);
//    tree->print();
}
