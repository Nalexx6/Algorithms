//
// Created by Win10Pro on 25.09.2020.
//

#ifndef LAB2_PARALLEL_QUICKSORT_SORT_H
#define LAB2_PARALLEL_QUICKSORT_SORT_H

#include <iostream>
#include <vector>
#include <ctime>
#include <random>

class Sort {

private:

    static int rand(int lo, int hi);

    static int partition( std::vector<int>& array, int& lo, int& hi, int& pivot);

    static void sort( std::vector<int>& bolts, std::vector<int>& nuts, int lo, int hi);

    static bool is_sorted(std::vector<int> &array);


public:

    static void shuffle(std::vector<int>& array, const int& lo, const int& hi);

    static void nuts_and_bolts_match(std::vector<int>& bolts, std::vector<int>& nuts, const int& n);



    static void print(std::vector<int>& array);








};


#endif //LAB2_PARALLEL_QUICKSORT_SORT_H
