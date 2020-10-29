//
// Created by Win10Pro on 10.09.2020.
//

#include <algorithm>
#include "Multiphase sort.h"


void Multiphase::save_to_bin_file(std::ofstream &file, const std::vector<int> &array) {


    for(auto& i:array){
        file.write((char*)&i, sizeof(i));
    }
//    std::cout<<array.size() << " numbers was successfully saved" << std::endl;

}

std::vector<std::ofstream> Multiphase::create_files(const int &file_quantity) {

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

std::vector<std::ifstream> Multiphase::reopen_files(const int &file_quantity) {

    std::string file_path, number = "a";
    std::vector<std::ifstream> files (file_quantity);
    for(int i = 0; i < file_quantity; i++) {

        number[0] = char(i + 65);
        file_path = "../src/Files/" + number + ".txt";

        files[i].open (file_path, std::ios::binary);

    }

    return files;

}

std::vector<int> Multiphase::load_all_file(std::ifstream &file) {

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

std::vector<int> Multiphase::count(const int &size, const int &files_quantity, int& limit) {
    //this function defines amount of subarrays, which will be written in each file before sorting

    std::vector<int> res;
    res.assign(files_quantity, 0);
    res[0] = 1;

    int needed_count = ceil(size/(double)limit);

    int max_index = 0;
    int max_size = 1;
    int chunk_counter = 0;



    while(chunk_counter < needed_count){
        chunk_counter = 0;

        for(int i = 0; i < res.size(); i++)
            if (res[i] > res[max_index]) {
                max_index = i;
                max_size = res[i];

            }

        for(int i = 0; i < res.size(); i++)
            if (i == max_index)
                res[i] = 0;

            else {
                res[i] += max_size;
                chunk_counter += res[i];
            }
    }

    limit = size / chunk_counter;

    return res;


}

std::vector<int> Multiphase::save_all_to_files(const std::vector<int> &array, std::vector<std::ofstream> &files, int &limit) {

    std::vector<int> sizes = Multiphase::count(array.size(), files.size(), limit);

    int sum = 0;
    for(auto i: sizes){
//        std::cout<<i<<"\n";
        sum += i;
    }

    std::vector<int> temp;
    int p = 0, j;
    for(std::size_t i = 0; i < files.size() ; i++){

        j = 0;
        for(; j < sizes[i] && sum > 0; j++) {
            temp.clear();

            for(int k = 0; k < limit && p < array.size(); k++){

                temp.emplace_back(array[p]);
                p++;

            }

            sum--;

            Sort::merge_sort(temp, 0, temp.size() - 1);

//            std::sort(temp.begin(), temp.end());
//            for(auto i: temp){
//                std::cout<<i <<"\t";
//            }
//            std::cout<<std::endl;

            Multiphase::save_to_bin_file(files[i], temp);



        }
        if(sum == 0){
            sizes[i] = j;
        }

    }

//    std::cout<<limit<<"\n";
    return sizes;

}

std::vector<int> Multiphase::sort(std::vector<std::ifstream> &read, std::vector<std::ofstream> &write, std::vector<int> &array,
                                  const int &limit, const int &size, std::vector<int>& chunks) {


    int out_index;
    int min_index;
    std::string lastFile = "res.txt", file_path, number = "a";

    std::vector<bool> in_use (read.size(), false);


    while (!check_all_merged(chunks)) {
        for (auto && i : in_use)
           i = false;

        out_index = get_output_file(chunks);
        min_index = get_min_file(chunks);

        std::cout << "Current number of chunks in files: ";
        for (int chunk : chunks)
            std::cout << chunk << " ";
        std::cout << std::endl;

        int minSize = chunks[min_index];

        read[out_index].close();
        number[0] = char(out_index + 65);
        file_path = "../src/Files/" + number + ".txt";
        write[out_index].open(file_path, std::ios::binary);

//        std::cout<<"start merging chunk" << std::endl;
        for (int i = 0; i < chunks[min_index]; i++) {
            merge_cur_chunk(chunks, in_use, read, write, out_index);
//            std::cout<<i << "\n";
//            mergeCurrentChunk(files, ifstreams, out, indexOutputFile);

        }
//        std::cout<<"chunk is merged chunk" << std::endl;

        for (int & chunk : chunks)
            if (chunk > 0)
                chunk -= minSize;
        chunks[out_index] += minSize;

        write[out_index].close();
        read[out_index].open(file_path, std::ios::binary);

        lastFile = file_path;
    }

    for (auto & i : read)
        i.close();

    std::cout << "\nSorted array is in " << lastFile << std::endl;

    return {};

}

void Multiphase::merge_cur_chunk(std::vector<int> &sizes, std::vector<bool>& in_use, std::vector<std::ifstream> &read,
                                 std::vector<std::ofstream> &write, const int &output_index) {

    for (int i = 0; i < sizes.size(); i++)
        if (sizes[i] > 0)
            in_use[i] = true;

    int min_index = 0, temp_number = 1001;

    std::vector<int> cur_numbers;
    for (int i = 0; i < read.size(); i++) {

        if (in_use[i]) {
            read[i].read((char *)&temp_number, sizeof(int));
            cur_numbers.push_back(temp_number);
            if (cur_numbers[min_index] > temp_number)
                min_index = i;
        }else{
            cur_numbers.push_back(1000);
        }

    }


    write[output_index].write((char*)&cur_numbers[min_index], sizeof(int));

    int pos = read[min_index].tellg();
    read[min_index].seekg(0, std::ios::end);
    int size = read[min_index].tellg();
    read[min_index].seekg(pos);

    clock_t start = clock();
    while(!check_merge_cur_chunk(in_use)){

        if (!in_use[min_index])
            for (int i = 0; i < in_use.size(); i++)
                if (in_use[i])
                    min_index = i;

        pos = read[min_index].tellg();

//        read[min_index].seekg(pos);
//        if(read[min_index].tellg() < size)
            read[min_index].read((char *)&temp_number, sizeof(int));

        if (read[min_index].tellg() == size || temp_number < cur_numbers[min_index]) {
            in_use[min_index] = false;
            cur_numbers[min_index] = 1000;
            read[min_index].seekg(pos);
        }else {
            cur_numbers[min_index] = temp_number;
//            if(read[min_index].tellg() == size)
//                in_use[min_index] = false;

        }


        for (int i = 0; i < in_use.size(); i++){
            if (in_use[i]){
                if (cur_numbers[i] < cur_numbers[min_index])
                    min_index = i;
            }
        }

        if (!check_merge_cur_chunk(in_use)) {
            write[output_index].write((char *) &cur_numbers[min_index], sizeof(cur_numbers[min_index]));
        }

    }
    clock_t end = clock();

//    std::cout<<end - start <<" ms" << std::endl;


}

int Multiphase::get_output_file(std::vector<int> &sizes) {

    int res = 0;
    bool flag = false;

    for (int i = 0; i < sizes.size() && !flag; i++)
        if (sizes[i] == 0) {
            res = i;
            flag = true;
        }

    return res;

}

int Multiphase::get_min_file(std::vector<int> &sizes) {

    int min_index = 0;

    while(sizes[min_index] == 0)
        min_index++;

    for (int i = 0; i < sizes.size(); i++)
        if (sizes[i] < sizes[min_index] && sizes[i] > 0)
            min_index = i;

    return min_index;

}

bool Multiphase::check_all_merged(std::vector<int> &sizes) {

    int sum = 0;

    for (int size : sizes)
        sum += size;

    return sum == 1;
}


bool Multiphase::check_merge_cur_chunk(std::vector<bool> &in_use) {

    for (auto && i : in_use)
        if (i)
        return false;

    return true;

}


bool Multiphase::is_sorted(std::vector<int> array) {

    for(std::size_t i = 1; i < array.size() - 1; i++){
        if(array[i] < array[i - 1])
            return false;

    }
    return true;

}


