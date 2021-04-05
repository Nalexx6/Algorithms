#include "PersistentSet.h"

int main() {
    auto* persistentSet = new PersistentSet<int>;

    int ar[10] = { 4, 2, 3, 6, 10, 5, 1, 8, 7, 9};

    for(int i = 0; i < 10; i++){

        persistentSet->insert(ar[i]);
        std::cout << "------------insert---------\n";
//        persistentSet->print();


    }

    for(int i = 1; i < 10; i++){

        persistentSet->erase(i);
        std::cout << "------------delete---------\n";


    }

    persistentSet->print();


}
