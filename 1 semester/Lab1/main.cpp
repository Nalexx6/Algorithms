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

    std::vector<int> sizes = Functions::count(size, file_quantity);
    for(int& i: sizes){
        std::cout<< i << " ";
    }
    std::cout<< "\n";

    std::string file_path, number = "a";
    std::vector<std::ofstream> files (file_quantity);
    for(int i = 0; i < file_quantity; i++) {

        number[0] = char(i + 48);
        file_path = "../src/Files/" + number + ".txt";

        files[i].open (file_path, std::ios::binary | std::ios::app);

    }
//    std::cout<<"efsdfdsf\n";
    Functions::save_to_bin_file(files[0], array);

    files[0].close();

    Sort::merge_sort(array, 0, size, false);

    for(auto i: array){
        std::cout<< i << " ";
    }

    std::cout<<"\n";


}