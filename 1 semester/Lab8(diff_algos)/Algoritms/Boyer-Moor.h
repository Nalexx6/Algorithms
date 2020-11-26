//
// Created by Win10Pro on 11/22/2020.
//

#ifndef LAB8_DIFF_ALGOS__BOYER_MOOR_H
#define LAB8_DIFF_ALGOS__BOYER_MOOR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

int bprefix(const std::string& a){

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

    return result[result.size() - 1];

}

int boyer_moor(const std::string& text, const std::string& pattern){

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
//    for(auto& i: shifts){
//
//        std::cout << i.second << " ";
//
//    }
//    std::cout << "\n";

//    int most_pref = bprefix(pattern);//length of most substring which is prefix and suffix of pattern simultaneously

    std::vector<int> suff (pattern.size() - 1, 0);
    for (int j = 1, maxZidx = 0, maxZ = 0; j < pattern.size(); ++j) {
        if (j <= maxZ) suff[j] = std::min(maxZ - j + 1, suff[j - maxZidx]);
        while (j + suff[j] < pattern.size() && text[pattern.size() - 1 - suff[j]] == text[pattern.size() - 1 - (j + suff[j])])
            suff[j]++;
        if (j + suff[j] - 1 > maxZ) {
            maxZidx = j;
            maxZ = j + suff[j] - 1;
        }
    }

    int i = 0;
    while (i <= pattern.size() - text.size()) {
        int j = 0;
        for (j = pattern.size() - 1; j >= 0 && pattern[j] == text[i + j]; --j);
        if (j < 0) {
            return i;
        }
        else i += std::max((suff[j + 1]), (int)(shifts[text[i + j]] - pattern.size() + j + 1));
    }

    return -1;



}

#endif //LAB8_DIFF_ALGOS__BOYER_MOOR_H
