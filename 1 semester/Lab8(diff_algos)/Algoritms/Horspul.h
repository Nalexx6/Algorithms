//
// Created by Win10Pro on 11/22/2020.
//

#ifndef LAB8_DIFF_ALGOS__HORSPUL_H
#define LAB8_DIFF_ALGOS__HORSPUL_H

#include <iostream>
#include <string>
#include <map>

int horspul(const std::string& text, const std::string& pattern){

    std::map<char, int> shifts;

    for(int i = 0; i < text.size(); i++){

        shifts[text[i]] = pattern.size();

    }

    for(int i = 0; i < pattern.size() - 1; i++){

        shifts[pattern[i]] = pattern.size() - i - 1;

    }

//    for(auto& i: shifts){
//
//        std::cout << i.first << " ";
//
//    }
//    std::cout << "\n";
//
//    for(auto& i: shifts){
//
//        std::cout << i.second << " ";
//
//    }
//    std::cout << "\n";

    int i = pattern.size() - 1, k;

    while (i < text.size()){

        k = 0;
        while (k < pattern.size() && pattern[pattern.size() - k - 1] == text[i - k])
            k++;

        if(k == pattern.size())
            return i - pattern.size() + 1;
        else
            i += shifts[text[i]];

    }

    return -1;

}


#endif //LAB8_DIFF_ALGOS__HORSPUL_H
