//
// Created by Win10Pro on 11.09.2020.
//

#include "Sort.h"

void Sort::merge(std::vector<int> &array, std::vector<int> &for_merge, int lo, int mid, int hi) {

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


}

void Sort::sort(std::vector<int> &array, std::vector<int> &for_merge, int lo, int hi) {

    if(hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    sort(array, for_merge, lo, mid);
    sort(array, for_merge, mid + 1, hi);
    merge(array, for_merge, lo ,mid, hi);

}

void Sort::merge_sort(std::vector<int> &array, int lo, int hi) {



        std::vector<int> for_merge (hi - lo + 1);

        sort(array, for_merge, lo, hi);
//        delete[] for_merge;

}




