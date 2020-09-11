//
// Created by Win10Pro on 10.09.2020.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

#include "Sort.h"
#include <string>

class Functions {

public:

    static void save_to_bin_file(std::ofstream& files,  const std::vector<int>& array);

    static std::vector<int> count(const int& size, const int& files_quantity);

    static void load_from_bin_file(std::vector<std::ifstream>& files,  const std::vector<int>& array);

};


#endif //LAB1_FUNCTIONS_H
