//
// Created by Win10Pro on 10/28/2020.
//

#ifndef LAB4_DIFF_SORTS_H
#define LAB4_DIFF_SORTS_H

#include <iostream>
#include <vector>
#include "Object.h"

class Diff_sorts {

public:
    static void sort_1_2(std::vector<Object<int>>& array);

    static void sort_1_3(std::vector<Object<int>>& array);

    static void sort_2_3(std::vector<Object<int>>& array);

    static bool is_sorted(std::vector<Object<int>>& array);

    static bool is_stable(std::vector<Object<int>>& array);



};


#endif //LAB4_DIFF_SORTS_H
