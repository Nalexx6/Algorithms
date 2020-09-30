//
// Created by Win10Pro on 25.09.2020.
//

#include "Sort.h"

int Sort::rand(int lo, int hi) {

    static std::random_device rd;
    static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
    static std::mt19937 mt(seq);

    std::uniform_int_distribution range(lo, hi);

    return range(mt);

}

void Sort::shuffle(std::vector<int> &array, const int &lo, const int &hi) {

    for(int i = 1; i < hi - lo + 1; i++){
        std::swap(array[lo + i], array[lo + rand(lo, lo + i) ]);
    }

}

int Sort::partition(std::vector<int> &array, int &lo, int &hi, int &pivot) {

    int i = lo;
    for (int j = lo; j < hi; j++){
        if (array[j] < pivot){

            std::swap(array[i], array[j]);
            i++;

        }

        else if (array[j] == pivot){

            std::swap(array[j], array[hi]);
            j--;
        }
    }
    std::swap(array[i], array[hi]);

    return i;

}

void Sort::sort(std::vector<int> &bolts, std::vector<int> &nuts, int lo, int hi) {

    if(hi <= lo)
        return;


    int pivot = partition(bolts, lo, hi, nuts[hi]);

    partition(nuts, lo, hi, bolts[pivot]);

    sort(bolts, nuts, lo, pivot - 1);

    sort(bolts, nuts, pivot + 1, hi);

}

void Sort::print(std::vector<int> &array) {

    for(auto& i: array){

        std::cout<< i <<" ";

    }
    std::cout<<std::endl;

}

bool Sort::is_sorted(std::vector<int> &array) {

    for(std::size_t i = 1; i < array.size() - 1; i++){
        if(array[i] < array[i - 1])
            return false;

    }
    return true;

}

void Sort::nuts_and_bolts_match(std::vector<int> &bolts, std::vector<int> &nuts, const int& n) {

    std::cout<<"Started sorting\n";
    clock_t start = clock();
    sort(bolts, nuts, 0, n - 1);
    clock_t end = clock();

    std::cout<<"Sort done in " << end - start << " ms\n";

    if(is_sorted(bolts))
        std::cout<<"Bolts are sorted\n";
    if(is_sorted(nuts))
        std::cout<<"Nuts are sorted\n";

//    std::cout<< "Matched nuts and bolts are: \n";
//
//    print(nuts);
//    print(bolts);




}
