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

    static void merge(std::vector<int>& array, std::vector<int>& for_merge, int lo, int mid, int hi, bool printing){

        for(int i = lo; i < hi + 1; i++){
            for_merge[i] = array[i];
        }
        int i = lo, j = mid + 1;
        for(int k = lo; k < hi + 1; k++){
            if(i > mid){
                array[k] = for_merge[j];
                j++;
            } else if(j > hi){
                array[k] = for_merge[i];
                i++;
            } else if(for_merge[i] > for_merge[j]){
                array[k] = for_merge[j];
                j++;
            } else{
                array[k] = for_merge[i];
                i++;
            }

        }
        if(printing){
            std::cout<<"Now we will merge our array\n";
            print_array(array, lo, hi);
        }

    }

    static void sort(std::vector<int>& array, std::vector<int>& for_merge, int lo, int hi, bool printing){

        if(hi <= lo)
            return;
        int mid = lo + (hi - lo) / 2;
        sort(array, for_merge, lo, mid, printing);
        sort(array, for_merge, mid + 1, hi, printing);
        merge(array, for_merge, lo ,mid, hi, printing);

    }

public:

    static void merge_sort(std::vector<int>& array, int lo, int hi, bool printing){

        std::vector<int> for_merge (hi - lo + 1);
        if(printing){
            std::cout<<"This merge sort use top-down algorithm\n";
            print_array(array, lo ,hi);

        }
        sort(array, for_merge, lo, hi, printing);
//        delete[] for_merge;

    }

    static void print_array(std::vector <int>& array, int& lo, int& hi){

    }

};


#endif //LAB1_SORT_H
