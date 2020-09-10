#include <iostream>

#include "src/Random.h"
#include "src/Sort.h"

int main() {

    int size, files, limit;

    std::cout<< "Please, enter the quantity of elements which you want to sort\n";
    std::cin>> size;

    std::cout<< "Please, enter the amount of files, which will take part in sort\n";
    std::cin>> files;

    std::cout<< "Please, enter the maximum limit of subarray, which could be read\n";
    std::cin>> limit;


    std::vector<int> array;

    for(int i = 0; i < size; i++){
        array.push_back(Random::rand(0, files * size));
    }

    for(auto i: array){
        std::cout<< i << " ";
    }
    std::cout<<"\n";

    Sort::merge_sort(array, 0, size, false);

    for(auto i: array){
        std::cout<< i << " ";
    }

    std::cout<<"\n";


}