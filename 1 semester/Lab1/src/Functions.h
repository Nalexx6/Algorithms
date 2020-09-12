//
// Created by Win10Pro on 10.09.2020.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

#include "Sort.h"
#include <string>

class Functions {

public:

    static void save_to_bin_file(std::ofstream& file,  const std::vector<int>& array);

    static std::vector<std::ofstream> create_files(const int& files_quantity);

    static void delete_files(std::vector<std::ofstream>& files);

    static void save_all_to_files(const std::vector<int>& array, std::vector<std::ofstream> &files, const int& limit);

    static void load_from_bin_file(std::vector<std::ifstream>& files,  const std::vector<int>& array);

    static std::vector<int> count(const int& size, const int& files_quantity);
};


#endif //LAB1_FUNCTIONS_H
