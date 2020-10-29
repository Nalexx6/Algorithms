#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Heap.h"

int main() {

    std::ifstream in("../data.txt");


    int n, d;
    std::vector<int> data;
    in >> n >> d;
    if (d < 1) {
        std::cout << "Incorrect d" << std::endl;
        return 0;
    }

    int temp;
    for (int i = 0; i < n; i++) {
        in >> temp;
        data.push_back(temp);
    }

    std::cout << "Start array: ";
    for (int i = 0; i < n; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    auto* heap = new Heap<int>(d);
    heap->build_heap(data);
    heap->print();

    std::string op;
    while (in >> op) {
        if (op == "inc") {

            int i;
            int v;
            in >> i >> v;
            heap->increase_key(i, v);
            std::cout << "Key in position " << i << " increased to " << v << std::endl;

        }
        else if (op == "ex") {

            std::cout << "Extracted max = " << heap->extract_max() << std::endl;

        }
        else {

            int v;
            in >> v;
            heap->insert(v);
            std::cout << "Inserted element " << v << std::endl;

        }

        heap->print();
    }

    int size = heap->size();
    for(int i = 0; i < size; i++){

        std::cout<< heap->extract_max() << " ";


    }



    return 0;

}
