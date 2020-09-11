//
// Created by Win10Pro on 10.09.2020.
//

#include "Functions.h"

void Functions::save_to_bin_file(std::ofstream &files, const std::vector<int> &array) {


    for(int i: array){
        files.write((char*)&i, sizeof(i));
    }

}

void Functions::load_from_bin_file(std::vector<std::ifstream> &files, const std::vector<int> &array) {

}

std::vector<int> Functions::count(const int &size, const int &files_quantity) {

    std::vector<int> res;
    res.assign(files_quantity, 0);
    res[files_quantity - 1] = 1;
    int sum = 1, min_index = 0, max_index = files_quantity - 1, new_max = 0, max_value;
    while (sum < size){
        max_value = res[max_index];
        for (int i = 0; i < res.size(); i++) {

            res[i] += max_value;
            if (res[new_max] < res[i] && i != max_index) {
                new_max = i;
            }

            sum += max_value;

        }

        sum -= res[max_index];
        min_index = max_index;
        res[min_index] = 0;
        max_index = new_max;
        new_max = min_index;

        std::cout<<sum<<"\n";
        for(int& i: res){
            std::cout<< i << " ";
        }
        std::cout<< "\n";

    }

    return res;
}
