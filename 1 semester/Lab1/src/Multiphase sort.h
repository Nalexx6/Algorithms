//
// Created by Win10Pro on 10.09.2020.
//

#ifndef LAB1_MULTIPHASE_SORT_H
#define LAB1_MULTIPHASE_SORT_H

#include "Sort.h"
#include <string>
#include <map>
#include <ctime>
#include <cmath>
class Multiphase {

    static int bin_search(int& value, std::vector<int>& array);

    static void save_to_bin_file(std::ofstream& file,  const int& value);

    static void save_to_bin_file(std::ofstream& file,  const std::vector<int>& array);

    static std::vector<int> load_all_file(std::ifstream& file);

    static int find_file(const std::vector<int>& array, const int& value, const std::vector<bool>& to_ignore);
public:


    static std::vector<std::ofstream> create_files(const int& files_quantity);

    static std::vector<std::ifstream> reopen_files(const int& file_quantity);

    static std::vector<int> count(const int& size, const int& files_quantity, int& limit);

    static std::vector<int> save_all_to_files(const std::vector<int>& array, std::vector<std::ofstream> &files, int& limit);

    static std::vector<int> sort(std::vector<std::ifstream> &read, std::vector<std::ofstream> & write,
                     std::vector<int>& array, const int& limit, const int& size, std::vector<int>& chunks);


    static bool is_sorted(std::vector<int> array);
};


#endif //LAB1_MULTIPHASE_SORT_H
