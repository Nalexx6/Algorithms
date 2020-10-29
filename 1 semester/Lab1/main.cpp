#include <iostream>

#include "src/Random.h"
//#include "src/Sort.h"
#include "src/Multiphase sort.h"
#include <ctime>

int main() {

    int size, file_quantity, limit;

    std::cout<< "Please, enter the quantity of elements which you want to sort\n";
    std::cin>> size;

    std::cout<< "Please, enter the amount of files, which will take part in sort\n";
    std::cin>> file_quantity;

    std::cout<< "Please, enter the maximum limit of subarray, which could be read\n";
    std::cin>> limit;

    std::vector<int> array;

    for(int i = 0; i < size; i++){
        array.push_back(Random::rand(0, size));
    }


    std::vector<std::ofstream> for_write = Multiphase::create_files(file_quantity);

    std::vector<int> sizes = Multiphase::save_all_to_files(array, for_write, limit);


    for(auto& f: for_write){
        f.close();

    }

    std::vector<std::ifstream> for_load = Multiphase::reopen_files(file_quantity);

    clock_t start = clock();

    std::vector<int> res = Multiphase::sort(for_load, for_write, array, limit, size, sizes);

    clock_t end = clock();

    std::cout<< "Sort was done in " << end - start <<" ms\n";


    for(auto& f: for_load){
        f.close();

    }

}


