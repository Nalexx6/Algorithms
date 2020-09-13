//
// Created by Win10Pro on 10.09.2020.
//

#include "Functions.h"

void Functions::save_to_bin_file(std::ofstream &file, const int &value) {

    file.write((char*)&value, sizeof(value));

}

void Functions::save_to_bin_file(std::ofstream &file, const std::vector<int> &array) {


    for(auto& i:array){
        file.write((char*)&i, sizeof(i));
    }
//    std::cout<<array.size() << " numbers was successfully saved" << std::endl;

}

std::vector<std::ofstream> Functions::create_files(const int &file_quantity) {

    std::string file_path, number = "a";
    std::vector<std::ofstream> files (file_quantity);
    for(int i = 0; i < file_quantity; i++) {

        number[0] = char(i + 65);
        file_path = "../src/Files/" + number + ".txt";

        files[i].open (file_path, std::ios::trunc);
        files[i].close();
        files[i].open (file_path, std::ios::binary);



    }

    return files;

}

std::vector<std::ifstream> Functions::reopen_files(const int &file_quantity) {

    std::string file_path, number = "a";
    std::vector<std::ifstream> files (file_quantity);
    for(int i = 0; i < file_quantity; i++) {

        number[0] = char(i + 65);
        file_path = "../src/Files/" + number + ".txt";

        files[i].open (file_path, std::ios::binary);

    }

    return files;

}

std::vector<int> Functions::load_all_file(std::ifstream &file) {

    std::vector<int> res;
    file.seekg(0, std::ios::end);
    int end_file = file.tellg(), temp;
    file.seekg(0, std::ios::beg);

    while(file.tellg() != end_file){
        file.read((char*) &temp, sizeof(temp));
        res.push_back(temp);
    }

    return res;

}

std::vector<std::vector<int>> Functions::count(const int &size, const int &files_quantity) {//this function defines amount of subarrays,
    // which will be written in each file before sorting

    std::vector<std::vector<int>> result;
    std::vector<int> res;
    res.assign(files_quantity, 0);
    res[files_quantity - 1] = 1;
    result.emplace_back(res);
    int  sum = 1, min_index = 0, max_index = files_quantity - 1, new_max = 0, max_value;
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

//        std::cout<<sum<<"\n";
//        for(int& i: res){
//            std::cout<< i << " ";
//        }
//        std::cout<< "\n";
        result.emplace_back(res);

    }

    return result;
}

void Functions::save_all_to_files(const std::vector<int> &array, std::vector<std::ofstream> &files, const int &limit) {

    std::vector<std::vector<int>> sizes = Functions::count(array.size(), files.size());

    std::vector<int> cur_sizes;
    cur_sizes.assign(files.size(), 0);
    for(auto & size : sizes){
        Sort::merge_sort(size, 0, size.size() - 1);
    }

//    std::cout<<"kekw"<<std::endl;

    for(auto & size : sizes){
        for(std::size_t j = 0; j < size.size()/2; j++) {
            int temp_1 = size[j];
            size[j] = size[size.size() - 1 - j];
            size[size.size() - 1 - j] = temp_1;
        }

    }

//    for(auto& i: sizes){
//        for(auto j: i){
//            std::cout<< j << " ";
//        }
//        std::cout<<std::endl;
//    }


    std::vector<int> temp;
    unsigned int index = 0, level = 1, k = 0;
    for(std::size_t i = 0; i < array.size(); i++){

//        std::cout<< array[i] << std::endl;
        temp.emplace_back(array[i]);
        i++;
//        std::cout<< array[i] << std::endl;

//        std::cout<< "gvy" <<std::endl;
        while(array[i - 1] <= array[i] && temp.size() < limit && i < array.size()){
            temp.emplace_back(array[i]);
//            std::cout<< array[i] << std::endl;
            i++;
//            std::cout<< "lol" <<std::endl;

        }
        i--;
//        std::cout<<"fdfdsf"<<std::endl;
//        for(auto i: temp){
//            std::cout<< i << " ";
//        }
//        std::cout<<std::endl << index << std::endl;
        Functions::save_to_bin_file(files[index], temp);
        cur_sizes[index]++;
        index = (index + 1) % files.size();
        while (cur_sizes[index] == sizes[level][index]){
            if(k == files.size()){
                level++;
            }
            index = (index + 1) % files.size();
            k++;
        }
//        std::cout<<k << " " << index << std::endl;
        k = 0;
        temp.clear();

    }

}

void Functions::sort(std::vector<std::ifstream> &read, std::vector<std::ofstream> &write, std::vector<int> &array,
                     const int &limit, const int &size) {

    std::vector<int> sizes (read.size()), memory;

    std::vector<bool> to_ignore, local_ignore;
    to_ignore.assign(read.size(), false);
    local_ignore.assign(read.size(), false);

    int empty_file = 0;
    for(std::size_t i = 0; i < read.size(); i++){

        read[i].seekg(0, std::ios::end);
        sizes[i] = read[i].tellg();
//        std::cout<< i << ": " << sizes[i] << std::endl;
        if(sizes[i] == 0){
            empty_file = i;
//            std::cout<<i << " ffdsfdsf\n";
        }
        read[i].seekg(0, std::ios::beg);

    }

    to_ignore[empty_file] = true;
    local_ignore[empty_file] = true;

    std::cout<< "Start of sorting" << std::endl;
    std::string number = "a", file_path;
    std::vector<int> cur_values(read.size());
    int new_empty = empty_file, value, next, file_pos, bin_pos, file_number;
//    std::vector<int> limits;
//    limits.assign(read.size(), 0);
    while(true) {

        read[empty_file].close();
        number[0] = char(empty_file + 65);
        file_path = "../src/Files/" + number + ".txt";
        write[empty_file].open(file_path, std::ios::binary);

        while (new_empty == empty_file) {

                for (std::size_t i = 0; i < read.size(); i++) {

                    if(!to_ignore[i]) {
                        read[i].read((char *) &value, sizeof(value));
                        memory.emplace_back(value);
                        cur_values[i] = value;
//                        limits[i]++;
                    }

                }


                Sort::merge_sort(memory, 0, memory.size() - 1);
                for(std::size_t j = 0; j < memory.size()/2; j++) {
                    int temp_1 = memory[j];
                    memory[j] = memory[memory.size() - 1 - j];
                    memory[memory.size() - 1 - j] = temp_1;
                }

//                for(auto i: memory){
//                    std::cout<<i << " ";
//                }
//                std::cout<<std::endl;

//                std::cout<<"gvy"<<std::endl;
                while(!memory.empty()){
//                    std::cout<<"gvy"<<std::endl;
                    value = memory[memory.size() - 1];
                    file_number = find_file(cur_values, value, local_ignore);
                    file_pos = read[file_number].tellg();
//                    std::cout<<value<< " " <<file_number<<" lol" <<std::endl;
                    save_to_bin_file(write[empty_file], value);

                    memory.pop_back();



                    if(file_pos != sizes[file_number]){
                        read[file_number].read((char *) &next, sizeof(next));

                        if (next >= value) {
                            bin_pos = bin_searh(next, memory);
                            if(bin_pos == memory.size()){
                                memory.emplace_back(next);
                            }
                            else{
                            memory.insert(memory.begin() + bin_pos, next);
                            }
//                            limits[accord[value]]++;
                            cur_values[file_number] = next;

                        } else{
                            read[file_number].seekg(file_pos);
//                            limits[accord[value]]--;
                            local_ignore[file_number] = true;


                        }
                    } else{
                        new_empty = file_number;
                        to_ignore[new_empty] = true;
                        local_ignore[new_empty] = true;

                    }


                }


//                std::cout << "lol\n";

                for(std::size_t i = 0; i < local_ignore.size(); i++){
                   local_ignore[i] = to_ignore[i];
                }
//                std::cin>>breakpoint;


        }

        to_ignore[empty_file] = false;
        local_ignore[empty_file] = false;
        write[empty_file].close();
        number[0] = char(empty_file + 65);
        file_path = "../src/Files/" + number + ".txt";
        read[empty_file].open(file_path, std::ios::binary);

        read[empty_file].seekg(0, std::ios::end);
        sizes[empty_file] = read[empty_file].tellg();
        read[empty_file].seekg(0, std::ios::beg);

        if(sizes[empty_file] == size * sizeof(array[0])){

            std::cout<<"Everything is in one file" << std::endl;
            break;

        }
//        std::cout<<"sdfdf\n";
        empty_file = new_empty;

//        std::cin>>breakpoint;
//        read[empty_file]. close();
//        number[0] = char(empty_file + 48);
//        file_path = "../src/Files/" + number + ".txt";
//        read[empty_file].open(file_path, std::ios::trunc);



    }

    std::cout<<"mmaasd" << std::endl;

    std::vector<int> res = load_all_file(read[empty_file]);


//    for(auto i: res){
//        std::cout<<i << " ";
//    }

    if(is_sorted(res)){
        std::cout<<"Our array was succesfully sorted\n";
    }
    std::cout<<"fsdfsdfsdf\n";

//    1 2 3 12 14 14 17 20 38 40

}

int Functions::find_file(const std::vector<int> &array, const int &value, const std::vector<bool>& to_ignore) {

    for(std::size_t i = 0; i < array.size(); i++){

        if(array[i] == value && !to_ignore[i])
            return i;

    }
    return -1;

}

bool Functions::is_sorted(std::vector<int> array) {

    for(std::size_t i = 1; i < array.size() - 1; i++){
        if(array[i] < array[i - 1])
            return false;

    }
    return true;

}

int Functions::bin_searh(int &value, std::vector<int> &array) {

    if(array.empty()){
        return 0;
    }
    if(array[array.size() - 1] >= value){
        return array.size();
    }
    if(array.size() == 1){
        if(array[0] < value)
            return 0;
        if(array[0] >= value)
            return 1;
    }
    int a = 0, b = array.size() - 1;
    int middle = 0;
    while(a < b){
        middle = (a + b) / 2;
        if(array[middle] >= value) {
            a = middle + 1;
            middle = (a + b) / 2;
        } else{
            b = middle;
//                middle = (a + b) / 2;
        }

    }
    return middle;

}
