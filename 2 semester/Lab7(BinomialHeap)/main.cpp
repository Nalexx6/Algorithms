#include "BinomialHeap.h"

int main() {

    auto* heap = new BinomialHeap<int>();
    int ar[10] = { 4, 2, 3, 6, 5, 1, 8, 7, 9};

    for(int i = 0; i < 9; i++){

        heap->insert(ar[i]);
        std::cout << "------------insert---------\n";
        heap->print();


    }

    heap->extractMin();
    std::cout<<"------------extract min-------------\n";
    heap->print();
}
