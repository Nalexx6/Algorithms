#include "PersistentSet.h"

int main() {
    auto* persistentSet = new PersistentSet<int>;

    int ar[10] = { 4, 2, 6, 3, 5, 1, 8, 7, 9};

    for(int i = 0; i < 9; i++){

        persistentSet->insert(ar[i]);
        std::cout << "------------insert---------\n";
        persistentSet->print();


    }
}
