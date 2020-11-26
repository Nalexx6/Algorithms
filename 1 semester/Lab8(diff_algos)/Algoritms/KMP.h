//
// Created by Win10Pro on 11/21/2020.
//

#ifndef LAB8_DIFF_ALGOS__KMP_H
#define LAB8_DIFF_ALGOS__KMP_H

#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefix(const std::string& a){

    std::vector<int> result;

    result.emplace_back(0);
    int k;

    for(int i = 1; i < a.length(); i++){

        k = result[i - 1];
//        std::cout <<k <<"\n";

        while (true) {
            if (a[i] == a[k]) {

                result.emplace_back(k + 1);
                break;

            }
            else if(k == 0){

                result.emplace_back(0);
                break;

            }
            else{

                k = result[k];

            }

//            std::cout << "fdsf\n";
        }

    }

    return result;

}

int kmp(std::string& b, std::string& a){

    std::vector<int> prefixes = prefix(a);

    std::string b_copy = b + b;
    int q = 0;

    for(int i = 0; i < b_copy.length(); i++){

        while (q > 0 && a[q] != b_copy[i]){

            q = prefixes[q];

        }
        if(a[q] == b_copy[i])
            q = q + 1;
        if(q == a.length())
            return i - a.length() + 1;

    }

    return -1;

}

#endif //LAB8_DIFF_ALGOS__KMP_H
