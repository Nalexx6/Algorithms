//
// Created by Win10Pro on 11/22/2020.
//

#ifndef LAB8_DIFF_ALGOS__RABIN_KARP_H
#define LAB8_DIFF_ALGOS__RABIN_KARP_H

#include <iostream>
#include <string>
#include <cmath>

const int q = 997;//main simple integer for algorithm
const int size = 100;//approximate quantity of possible symbols(95 if not round)
int h;


int hash(const std::string& a){

    int res = 0;
    for(int i = 0; i < a.size(); i++){

        res = (res * size + int(a[i])) % q;

    }

    return res;

}

bool check(const std::string& text, const std::string& pattern, const int& hpattern, const int& htext,
           const int& shift){

    if(hpattern != htext)
        return false;

    for(int i = 0; i < pattern.size(); i++){

        if(pattern[i] != text[shift + i])
            return false;

    }


    return true;

}

int rabin_karp(const std::string& text, const std::string& pattern){

    h = pow(size, pattern.size() - 1);

    int hpattern = hash(pattern);

    std::cout << "ffdf\n";

    int htext;

    std::string temp;

    for(int j = 0; j < pattern.size(); j++){

        temp+= text[j];

    }

    htext = hash(temp);

    for(int i = 0; i < text.size() - pattern.size() + 1; i++){

//        std::cout << htext << "\n";

        if(check(text, pattern, hpattern, htext, i))
            return i;
        else{
            htext = ((htext + int(text[i]) * (q - h % q)) * size + int(text[i + pattern.size()])) % q;
//            std::cout << htext << "\n";
        }

    }

    return -1;

}


#endif //LAB8_DIFF_ALGOS__RABIN_KARP_H
