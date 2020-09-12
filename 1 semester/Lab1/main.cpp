#include <iostream>

#include "src/Random.h"
//#include "src/Sort.h"
#include "src/Functions.h"

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
        array.push_back(Random::rand(0, file_quantity * size));
    }

    for(auto i: array){
        std::cout<< i << " ";
    }
    std::cout<<"\n";


    std::vector<std::ofstream> files = Functions::create_files(file_quantity);
    std::cout << "sfsdfsd\n";
    Functions::save_all_to_files(array, files, limit);
//
//    Functions::save_to_bin_file(files[0], array);
//    Functions::save_to_bin_file(files[0], array);


    for(auto& f: files){
//        std::remove((const char *) f);
    }


}