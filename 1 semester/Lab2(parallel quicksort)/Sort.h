//
// Created by Win10Pro on 25.09.2020.
//

#ifndef LAB2_PARALLEL_QUICKSORT_SORT_H
#define LAB2_PARALLEL_QUICKSORT_SORT_H

#include <iostream>
#include <vector>

class Sort {

private:

    static int partition( std::vector<int>& bolts, std::vector<int>& nuts, int& lo, int& hi){



    }

    static void sort( std::vector<int>& bolts, std::vector<int>& nuts, int lo, int hi){

        if(hi <= lo)
            return;

        int j = partition(bolts, nuts, lo, hi);

        sort(bolts, nuts, lo, j - 1);

        sort(bolts, nuts, j + 1, hi);



    }

public:

    static void shuffle(std::vector<int>& array, const int& lo, const int& hi){

        for(int i = 1; i < hi - lo + 1; i++){
            std::swap(array[lo + i], array[lo + rand() % i]);
        }

    }




};


#endif //LAB2_PARALLEL_QUICKSORT_SORT_H
