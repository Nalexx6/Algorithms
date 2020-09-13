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
        array.push_back(Random::rand(0, size * 2));
    }

//    for(auto i: array){
//        std::cout<< i << " ";
//    }
//    std::cout<<"\n";


    std::vector<std::ofstream> for_write = Functions::create_files(file_quantity);
//    std::cout << "sfsdfsd\n";
    Functions::save_all_to_files(array, for_write, limit);
//
//    Functions::save_to_bin_file(files[0], array);
//    Functions::save_to_bin_file(files[0], array);


    for(auto& f: for_write){
        f.close();

    }

//    std::cout<< "Start of sorting" << std::endl;

    std::vector<std::ifstream> for_load = Functions::reopen_files(file_quantity);

//    std::cout<< "Start of sorting" << std::endl;

    Functions::sort(for_load, for_write, array, limit, size);


    for(auto& f: for_load){
        f.close();

    }

}