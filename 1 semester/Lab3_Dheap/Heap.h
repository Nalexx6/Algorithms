//
// Created by Win10Pro on 10/14/2020.
//

#ifndef LAB3_DHEAP_HEAP_H
#define LAB3_DHEAP_HEAP_H

#include <iostream>
#include <vector>

template <typename T>
class Heap {


private:

    int _d;
    std::vector<T> _array;

public:

    Heap(int d) : _d(d) {}
    ~Heap();

    int d(){ return _d;}
    std::vector<T> array(){ return _array;}

    void heapify(int i){

        int max_p = i;
        float max_v = _array[i];
        for(int k = 1; k <= _d; k++){
            int p = _d * i + k;
            if (p >= _array.size()){
                break;
            }
            if (_array[p] > max_v){
                max_v = _array[p];
                max_p = p;
            }
        }
        if(max_p != i) {
            std::swap(_array[i], _array[max_p]);
            heapify(max_p);
        }

    }
    void build_heap(const std::vector<T>& input){

        for(auto i: input){

            _array.push_back(i);

        }

        for(int i = input.size() - 1; i >= 0; i--){

            heapify(i);

        }

    }
    void print(){

        for(auto i: _array) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

    }

    void increase_key(int i, const T& t){

        if(i == 0){
            _array[0] = t;
            return;
        }

        int p = (i - 1) / _d;
        if(_array[p] < t){

            _array[i] = _array[p];
            increase_key(p, t);

        }
        else{
            _array[i] = t;
        }

    }
    T extract_max(){

        T maxV = _array[0];
        std::swap(_array[0], _array[_array.size() - 1]);
        _array.pop_back();

        heapify(0);

        return maxV;

    }
    void insert(const T& t){

        _array.push_back(t);
        increase_key(_array.size() - 1, t);

    }






};


#endif //LAB3_DHEAP_HEAP_H
