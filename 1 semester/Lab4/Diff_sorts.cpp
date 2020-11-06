//
// Created by Win10Pro on 10/28/2020.
//

#include "Diff_sorts.h"

void Diff_sorts::sort_1_2(std::vector<Object<int>> &array) {

    std::vector<Object<int>> res;
    res = array;

    int index = 0;

    for(auto & i : array){

        if(i.key() == 0){

            res[index] = i;
            index++;

        }

    }

    for(auto & i : array){

        if(i.key() == 1){

            res[index] = i;
            index++;

        }

    }

    array.clear();
    for(auto& i: res){

        array.emplace_back(i);

    }

    res.clear();
}

void Diff_sorts::sort_1_3(std::vector<Object<int>> &array) {


    int counter = 0;

    for(auto& i: array){

        if(i.key() == 0)
            counter++;

    }

//    std::cout<<counter << "\n";

    int i = 0, j = array.size() - 1;
    while(i < counter){

        while(array[i].key() == 0){

            i++;

        }

        if(i >= counter)
            break;

        while (array[j].key() == 1){

            j--;

        }

//        std::cout<< i << " " << j << "\n";

        std::swap(array[i], array[j]);

        i++;
        j--;

    }

}

void Diff_sorts::sort_2_3(std::vector<Object<int>> &array) {

//    Object<int> temp ();

    for (int i = 0; i < array.size(); i++) {
        Object<int> temp = array[i];
        int j;
        for (j = i; j > 0 && array[j-1].key() > temp.key();j--) {
            array[j] = array[j-1];
        }
        array[j] = temp;

    }

}

bool Diff_sorts::is_sorted(std::vector<Object<int>> &array) {


    for(int i = 0; i < array.size() - 1; i++){

        if(array[i].key() > array[i + 1].key())
            return false;

    }

    return true;

}

bool Diff_sorts::is_stable(std::vector<Object<int>> &array) {

    for(int i = 0; i < array.size() - 1; i++){

        if(array[i].key() == array[i + 1].key())
            if(array[i].element() > array[i + 1].element())
                return false;

    }

    return true;

}
