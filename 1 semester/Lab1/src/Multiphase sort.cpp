//
// Created by Win10Pro on 10.09.2020.
//

#include "Multiphase sort.h"

void Multiphase::save_to_bin_file(std::ofstream &file, const int &value) {

    file.write((char*)&value, sizeof(value));

}

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
    res[files_quantity - 1] = 1;
    int  sum = 1, min_index = 0, max_index = files_quantity - 1, new_max = 0, max_value;
    int needed_chunks = ceil(size/(double)limit);
    while (sum < needed_chunks){

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
    }

//    Sort::merge_sort(res, 0, res.size() - 1);
//    for (int i = 0; i < res.size() / 2; ++i) {
//
//    }

    limit = size / sum;

    return res;
}

std::vector<int> Multiphase::save_all_to_files(const std::vector<int> &array, std::vector<std::ofstream> &files, int &limit) {

    std::vector<int> sizes = Multiphase::count(array.size(), files.size(), limit);

    int sum = 0;
    for(auto i: sizes){
        std::cout<<i<<"\n";
        sum += i;
    }


    std::vector<int> temp;
    int p = 0, j;
    for(std::size_t i = 0; i < files.size() ; i++){

        j = 0;
        for(; j < sizes[i] && sum > 0; j++) {

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

            temp.clear();

        }
        if(sum == 0){
            sizes[i] = j;
        }


    }

    std::cout<<limit<<"\n";
    return sizes;



//    for (int i = 0; i < data.countOfFiles; i++){
//
//        int newElement, j = 0;
//        for (; j < countsOfChunksInEachFiles[i] && neededCountOfChunks > 0; j++){
//            newFile.currentChunk.clear();
//
//            for (int k = 0; k < data.sizeOfChunk && !in.eof(); k++) {
//                in.read((char *)&newElement, sizeof(int));
//                newFile.currentChunk.push_back(newElement);
//            }
//
//            neededCountOfChunks--;
//            sort(newFile.currentChunk.begin(), newFile.currentChunk.end());
//            for (auto number : newFile.currentChunk) {
//                out.write((char *) &number, sizeof(number));
//            }
//        }
//        if (neededCountOfChunks == 0)
//            newFile.countOfChunks = j;
//        else
//            newFile.countOfChunks = countsOfChunksInEachFiles[i];
//
//        files.push_back(newFile);
//        out.close();
//    }

}

std::vector<int> Multiphase::sort(std::vector<std::ifstream> &read, std::vector<std::ofstream> &write, std::vector<int> &array,
                                  const int &limit, const int &size, std::vector<int>& chunks) {

    std::vector<int> sizes (read.size()), memory;

    std::vector<bool> to_ignore, local_ignore;
    to_ignore.assign(read.size(), false);
    local_ignore.assign(read.size(), false);

    int sum = 0;
    for(int i : chunks){
        sum += i;
    }
    std::cout<<"sum = " << sum<<"\n";

    int empty_file = 0, ignore_sum = 0;
    for(std::size_t i = 0; i < read.size(); i++){

        read[i].seekg(0, std::ios::end);
        sizes[i] = read[i].tellg();
//        std::cout<< i << ": " << sizes[i] << std::endl;
        if(sizes[i] == 0){
            to_ignore[i] = true;
            local_ignore[i] = true;
            empty_file = i;
            ignore_sum++;
//            std::cout<<i << " ffdsfdsf\n";
        }
        read[i].seekg(0, std::ios::beg);

    }

//    to_ignore[empty_file] = true;
//    local_ignore[empty_file] = true;

    std::cout<< "Start of sorting" << std::endl;
    std::string number = "a", file_path;
    std::vector<int> cur_values(read.size());
    int new_empty = empty_file, value, next, file_pos, bin_pos, file_number;
    std::vector<int> limits;
    limits.assign(read.size(), 0);
    while(true) {



        read[empty_file].close();
        number[0] = char(empty_file + 65);
        file_path = "../src/Files/" + number + ".txt";
        write[empty_file].open(file_path, std::ios::binary);
        clock_t start = clock();
        int chunk_counter = 0;
        for(auto i: chunks){
            std::cout<<i<<"\t";
        }
        std::cout<<"\n";
        while (new_empty == empty_file) {

            for (std::size_t i = 0; i < read.size(); i++) {

                if(!to_ignore[i]) {
                    read[i].read((char *) &value, sizeof(value));
                    memory.emplace_back(value);
                    cur_values[i] = value;
                    limits[i]++;
                }

            }


            Sort::merge_sort(memory, 0, memory.size() - 1);
            for(std::size_t j = 0; j < memory.size()/2; j++) {
                int temp_1 = memory[j];
                memory[j] = memory[memory.size() - 1 - j];
                memory[memory.size() - 1 - j] = temp_1;
            }


            clock_t start_1 = clock();

            while(!memory.empty()){

                value = memory[memory.size() - 1];
                file_number = find_file(cur_values, value, local_ignore);
                file_pos = read[file_number].tellg();
//                    std::cout<<value<< " " <<file_number<<" lol" <<std::endl;
                save_to_bin_file(write[empty_file], value);

//                for(auto i : memory){
//                    std::cout << i << "\t";
//                }
//                std::cout<<std::endl;
                memory.pop_back();



                if(file_pos != sizes[file_number]){
                    read[file_number].read((char *) &next, sizeof(next));

                    if (next >= value && (limits[file_number] < limit || (sum == read.size() - 1)) ) {
                        bin_pos = bin_search(next, memory);
                        if(bin_pos == memory.size()){
                            memory.emplace_back(next);
                        }
                        else{
                        memory.insert(memory.begin() + bin_pos, next);
                        }
                        limits[file_number]++;
                        cur_values[file_number] = next;

                    } else{
                        read[file_number].seekg(file_pos);
//                        limits[file_number] = 0;
                        local_ignore[file_number] = true;
//                        ignore_sum++;


                    }
                } else{
                    new_empty = file_number;
                    to_ignore[new_empty] = true;
                    local_ignore[new_empty] = true;

                }


            }
            clock_t end_1 = clock();
//            std::cout<<"Getting 1 chunk from all files "<<end_1 - start_1<<"ms\n";


//                std::cout << "lol\n";
            for(int & i : limits){
                i = 0;
            }


            for(std::size_t i = 0; i < local_ignore.size(); i++){
               local_ignore[i] = to_ignore[i];
            }
//                std::cin>>breakpoint;

            chunk_counter++;
        }
        clock_t end = clock();
        std::cout<<"File " << new_empty <<" is empty "<<end - start<<"ms\n";
//        std::cout<<new_empty<<"\n";
        for(std::size_t i = 0; i < chunks.size(); i++){
            if(i == empty_file){
                chunks[i] = chunks[new_empty];

            }
            else if(i != new_empty) {
                chunks[i] -= chunks[new_empty];
                sum -= chunks[new_empty];
            }
        }
        chunks[new_empty] = 0;
        std::cout<<"sum = " << sum<<"\n";



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

        for(int i = 0; i < sizes.size(); i++){
            std::cout<< i << ": " << sizes[i] << "\n";
        }
//        std::cout<<"sdfdf\n";
        empty_file = new_empty;

//        std::cin>>breakpoint;
//        read[empty_file]. close();
//        number[0] = char(empty_file + 48);
//        file_path = "../src/Files/" + number + ".txt";
//        read[empty_file].open(file_path, std::ios::trunc);



    }

    return load_all_file(read[empty_file]);


//    for(auto i: res){
//        std::cout<<i << " ";
//    }

//    if(is_sorted(res)){
//        std::cout<<"Our array was succesfully sorted and has size = " << res.size() << "\n";
//    }


}

int Multiphase::find_file(const std::vector<int> &array, const int &value, const std::vector<bool>& to_ignore) {

    for(std::size_t i = 0; i < array.size(); i++){

        if(array[i] == value && !to_ignore[i])
            return i;

    }
    return -1;

}

bool Multiphase::is_sorted(std::vector<int> array) {

    for(std::size_t i = 1; i < array.size() - 1; i++){
        if(array[i] < array[i - 1])
            return false;

    }
    return true;

}

int Multiphase::bin_search(int &value, std::vector<int> &array) {

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
