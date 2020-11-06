#include <iostream>
#include <ctime>
#include <random>

int rand(int lo, int hi) {

    static std::random_device rd;
    static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
    static std::mt19937 mt(seq);

    std::uniform_int_distribution range(lo, hi);

    return range(mt);
}

int* multiply(int* A, int* B, const int& power){

    int* res = new int[power * power];

    int temp_value = 0;
    for(int i = 0; i < power; i++){

        for(int j = 0; j < power; j++){

            for(int k = 0; k < power; k++){

                temp_value += A[power * i + k] * B[power * k + j];

            }

            res[power * i + j] = temp_value;
            temp_value = 0;

        }

    }

    return res;

}

int main() {

    int power = 2;

    std::cout << "Please enter the power of your matrix\n";
    std::cin >> power;

    int *A = new int [power * power];
    int *B = new int [power * power];

    for(int i = 0; i < power; i++){

        for(int j = 0; j < power; j++){

            A[power * i + j]  = rand(0 , 10);
            B[power * i + j]  = rand(0 , 10);

        }

    }

    clock_t start = clock();
    int* res = multiply(A, B, power);
    clock_t end = clock();

//    for(int i = 0; i < power; i++){
//
//        for(int j = 0; j < power; j++){
//
//            std::cout<< res[power * i + j] << "\t";
//
//        }
//
//        std::cout << "\n";
//
//    }

    std::cout<<"Multiplying was done in " << end - start << "ms\n";

    return 0;
}
