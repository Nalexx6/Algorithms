//
// Created by Win10Pro on 10.09.2020.
//

#include "Functions.h"



void Functions::save_to_bin_file(std::ofstream &file, const std::vector<int> &array) {


    for(int i: array){
        file.write((char*)&i, sizeof(i));
    }
    std::cout<<array.size() << " numbers was successfully saved" << std::endl;

}

std::vector<std::ofstream> Functions::create_files(const int &file_quantity) {

    std::string file_path, number = "a";
    std::vector<std::ofstream> files (file_quantity);
    for(int i = 0; i < file_quantity; i++) {

        number[0] = char(i + 48);
        file_path = "../src/Files/" + number + ".txt";

        files[i].open (file_path, std::ios::trunc);
        files[i].open (file_path, std::ios::binary);



    }

    return files;

}

void Functions::delete_files(std::vector<std::ofstream> &files) {

    std::string file_path, number = "a";
    std::vector<std::string> paths (files.size());
    for(int i = 0; i < files.size(); i++) {

        number[0] = char(i + 48);
        paths[i] = "../src/Files/" + number + ".txt";

//        std::remove(paths[i]);

    }

}

std::vector<int> Functions::count(const int &size, const int &files_quantity) {//this function defines amount of subarrays,
    // which will be written in each file before sorting

    std::vector<int> res;
    res.assign(files_quantity, 0);
    res[files_quantity - 1] = 1;
    int sum = 1, min_index = 0, max_index = files_quantity - 1, new_max = 0, max_value;
    while (sum < size){
        max_value = res[max_index];
        for (std::size_t i = 0; i < res.size(); i++) {

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

void Functions::save_all_to_files(const std::vector<int> &array, std::vector<std::ofstream> &files, const int &limit) {

    std::vector<int> sizes = Functions::count(array.size(), files.size());

    std::vector<int> cur_sizes (files.size());
    Sort::merge_sort(sizes, 0, sizes.size(), false);
//    std::cout<<"kekw"<<std::endl;
    for(std::size_t i = 0; i <= sizes.size()/2; i++){

        int temp_1 = cur_sizes[i];
        cur_sizes[i] = cur_sizes[sizes.size() - 1 - i];
        cur_sizes[sizes.size() - 1 - i] = temp_1;

    }

    std::vector<int> temp;
    unsigned int index = 0;
    for(int i = 0; i < array.size(); i++){

//        std::cout<< array[i] << std::endl;
        temp.emplace_back(array[i]);
        i++;
//        std::cout<< array[i] << std::endl;

//        std::cout<< "gvy" <<std::endl;
        while(array[i - 1] <= array[i] && temp.size() <= limit && i < array.size()){
            temp.emplace_back(array[i]);
            std::cout<< array[i] << std::endl;
            i++;
//            std::cout<< "lol" <<std::endl;

        }
        i--;
//        44 53 86 22 100 44 5 51 66 94 67 53 24 34 14 5 98 88 88 39 1 26
//        std::cout<<"fdfdsf"<<std::endl;
        Functions::save_to_bin_file(files[index], temp);
        cur_sizes[index]++;
        index = (index + 1) % files.size();
        while (cur_sizes[index] == sizes[index]){
            index = (index + 1) % files.size();
        }
        temp.clear();

    }

}

void Functions::load_from_bin_file(std::vector<std::ifstream> &files, const std::vector<int> &array) {



}
