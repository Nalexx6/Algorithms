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


//resize matrix to power = 2 ^ k
int* resize(int* A, int& power){

    int k = 1;
    while(power > k){

        k *= 2;

    }

//    if(k == power)
//        return A;

    int* resized = new int [k * k];

    for(int i = 0; i < k; i++){

        for(int j = 0; j < k; j++){

            if(i >= power || j >= power)
                resized[k * i + j]  = 0;
            else
                resized[k * i + j] = A[power * i + j];

        }

    }

    power = k;
    return resized;

}

//classic multiplying algorithm
void multiply(const int* A, const int* B, const int& power, int* R){

//    int* res = new int[power * power];

    int temp_value = 0;
    for(int i = 0; i < power; i++){

        for(int j = 0; j < power; j++){

            for(int k = 0; k < power; k++){

                temp_value += A[power * i + k] * B[power * k + j];

            }

            R[power * i + j] = temp_value;
            temp_value = 0;

        }

    }

//    return res;

}

//add two matrices
void add_matrix( const int& power, const int* A, const int* B, int* R){

    for(int i = 0; i < power; i++){

        for(int j = 0; j < power; j++){

            R[power * i + j]  = A[power * i + j] + B[power * i + j];

        }

    }

}

//subtract one matrix from another
void sub_matrix(const int& power, const int* A, const int* B, int* R){

    for(int i = 0; i < power; i++){

        for(int j = 0; j < power; j++){

            R[power * i + j]  = A[power * i + j] - B[power * i + j];

        }

    }

}

void strassen(int power, int* A, int* B, int* R){

    int* A11 = new int [power * power / 4];
    int* A12 = new int [power * power / 4];
    int* A21 = new int [power * power / 4];
    int* A22 = new int [power * power / 4];

    int* B11 = new int [power * power / 4];
    int* B12 = new int [power * power / 4];
    int* B21 = new int [power * power / 4];
    int* B22 = new int [power * power / 4];

    int* R11 = new int [power * power / 4];
    int* R12 = new int [power * power / 4];
    int* R21 = new int [power * power / 4];
    int* R22 = new int [power * power / 4];

    int* M1 = new int [power * power / 4];
    int* M2 = new int [power * power / 4];
    int* M3 = new int [power * power / 4];
    int* M4 = new int [power * power / 4];
    int* M5 = new int [power * power / 4];
    int* M6 = new int [power * power / 4];
    int* M7 = new int [power * power / 4];

    int* AA = new int [power * power / 4];
    int* BB = new int [power * power / 4];


    if (power == 2) {

        return multiply(A, B, power, R);

    }
    else {

        //initialization of auxiliary matrices
        for (int i = 0; i < power / 2; i++) {
            for (int j = 0; j < power / 2; j++) {
                A11[power * i / 2 + j] = A[power * i + j];
                A12[power * i / 2 + j] = A[power * i + j + power / 2];
                A21[power * i / 2 + j] = A[power * (i + power / 2) + j];
                A22[power * i / 2 + j] = A[power * (i + power / 2) + j + power / 2];

                B11[power * i / 2 + j] = B[power * i + j];
                B12[power * i / 2 + j] = B[power * i + j + power / 2];
                B21[power * i / 2 + j] = B[power * (i + power / 2) + j];
                B22[power * i / 2 + j] = B[power * (i + power / 2) + j + power / 2];
            }
        }

        //calculating M1 = (A11 + A22) × (B11 + B22)
        add_matrix(power / 2, A11, A22, AA);
        add_matrix(power / 2, B11, B22, BB);
        strassen(power / 2, AA, BB, M1);

        //calculating M2 = (A21 + A22) × B11
        add_matrix(power / 2, A21, A22, AA);
        strassen(power / 2, AA, B11, M2);

        //calculating M3 = A11 × (B12 - B22)
        sub_matrix(power / 2, B12, B22, BB);
        strassen(power / 2, A11, BB, M3);

        //calculating M4 = A22 × (B21 - B11)
        sub_matrix(power / 2, B21, B11, BB);
        strassen(power / 2, A22, BB, M4);

        //calculating M5 = (A11 + A12) × B22
        add_matrix(power / 2, A11, A12, AA);
        strassen(power / 2, AA, B22, M5);

        //calculating M6 = (A21 - A11) × (B11 + B12)
        sub_matrix(power / 2, A21, A11, AA);
        add_matrix(power / 2, B11, B12, BB);
        strassen(power / 2, AA, BB, M6);

        //calculating M7 = (A12 - A22) × (B21 + B22)
        sub_matrix(power / 2, A12, A22, AA);
        add_matrix(power / 2, B21, B22, BB);
        strassen(power / 2, AA, BB, M7);

        //calculating C11 = M1 + M4 - M5 + M7
        add_matrix(power / 2, M1, M4, AA);
        sub_matrix(power / 2, M7, M5, BB);
        add_matrix(power / 2, AA, BB, R11);

        //calculating C12 = M3 + M5
        add_matrix(power / 2, M3, M5, R12);

        //calculating C21 = M2 + M4
        add_matrix(power / 2, M2, M4, R21);

        //calculating C22 = M1 - M2 + M3 + M6
        sub_matrix(power / 2, M1, M2, AA);
        add_matrix(power / 2, M3, M6, BB);
        add_matrix(power / 2, AA, BB, R22);

        //merge all results to R
        for (int i = 0; i < power / 2; i++) {
            for (int j = 0; j < power / 2; j++) {
                R[power * i + j] = R11[power * i / 2 + j];
                R[power * i + j + power / 2] = R12[power * i / 2 + j];
                R[power * (i + power / 2) + j] = R21[power * i / 2 + j];
                R[power * (i + power / 2) + j + power / 2] = R22[power * i / 2 + j];
            }
        }
    }

    delete [] A11, delete [] A12, delete [] A21, delete [] A22;
    delete [] B11, delete [] B12, delete [] B21, delete [] B22;
    delete [] R11, delete [] R12, delete [] R21, delete [] R22;
    delete [] M1, delete [] M2, delete [] M3, delete [] M4, delete [] M5, delete [] M6, delete [] M7;
    delete [] AA, delete [] BB;


}

void strassen_multiply(int* A, int* B, const int& power, int* R){

//    int* R = new int [power * power];

    if(power == 2){

        return multiply(A, B, power, R);

    }
    int new_power = power;


    int *a_copy = resize(A, new_power);
    new_power = power;
    int *b_copy = resize(B, new_power);


    int* result = new int [new_power * new_power];

    strassen(new_power, a_copy, b_copy, result);

    for(int i = 0; i < new_power; i++){

        for(int j = 0; j < new_power; j++){

            if(i < power && j < power)
                R[power * i + j] = result[new_power * i + j];

        }


    }

    delete [] a_copy, delete [] b_copy, delete [] result;


}

void print(const int* A, const int& power){

    for(int i = 0; i < power; i++){

        for(int j = 0; j < power; j++){

            std::cout<< A[power * i + j] << "\t";

        }

        std::cout << "\n";

    }

}

bool equal(const int* A, const int* B, const int& power){

    for(int i = 0; i < power * power; i++){

        if(A[i] != B[i])
            return false;

    }

    return true;

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

//    print(A, power);
//    std::cout << "\n";
//    print(B, power);
//    std::cout << "\n";


    std::cout << "Classic multiplying started...\n";

    clock_t start = clock();
    int* res = new int [power * power];
    multiply(A, B, power, res);
    clock_t end = clock();


//    print(res, power);

    std::cout<<"Classic multiplying was done in " << end - start << "ms\n\n";

    std::cout << "Strassen multiplying started...\n";
    start = clock();
    int* res1 = new int [power * power];
    strassen_multiply(A, B, power, res1);
    end = clock();

//    print(res1, power);

    std::cout<<"Strassen multiplying was done in " << end - start << "ms\n\n";

    if(equal(res, res1, power))
        std::cout << "Results of multiplying are equal\n";
    else
        std::cout << "Results of multiplying are not equal\n";

    return 0;
}
