//
// Created by Win10Pro on 10.09.2020.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

#include "Sort.h"

template <typename T>
class Functions {

public:

    static void save_to_bin_file(std::vector<std::ofstream>& files, const int& index,  const std::vector<T>& array){
        for(auto i: array){
            files[index].write((char*)&i, sizeof(i));
        }
    }

    static void load_from_bin_file(std::vector<std::ifstream>& files,  const std::vector<T>& array){



    }

};


#endif //LAB1_FUNCTIONS_H
