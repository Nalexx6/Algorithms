//
// Created by Win10Pro on 10.09.2020.
//

#ifndef LAB1_SORT_H
#define LAB1_SORT_H

#include <iostream>
#include <vector>
#include <fstream>


class Sort {

private:

    static void merge(std::vector<int>& array, std::vector<int>& for_merge, int lo, int mid, int hi, bool printing);

    static void sort(std::vector<int>& array, std::vector<int>& for_merge, int lo, int hi, bool printing);

public:

    static void merge_sort(std::vector<int>& array, int lo, int hi, bool printing);

    static void print_array(std::vector <int>& array, int& lo, int& hi);

};


#endif //LAB1_SORT_H
