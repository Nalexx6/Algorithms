#include <iostream>
#include <ctime>

#include "Algoritms/KMP.h"
#include "Algoritms/Rabin-karp.h"
#include "Algoritms/Horspul.h"
#include "Algoritms/Boyer-Moor.h"

int naive(const std::string& text, const std::string& pattern) {

    bool found;
    for (int i = 0; i < text.size(); i++) {

        found = true;
        for (int j = 0; j < pattern.size(); j++) {

            if (pattern[j] != text[i + j])
                found = false;
        }
        if (found)
            return i;

    }

    return -1;

}

int main() {

    std::string pattern = "hello", text = "hell sadd yollo simultaneously coincidence hello world";

    std::cout << "Naive\n";
    clock_t start = clock();
    int shift = naive(text, pattern);
    clock_t end = clock();
    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n"
                                                                         "time is: " << end - start << "ms\n";
    std::cout << "Horspul\n";
    start = clock();
    shift = horspul(text, pattern);
    end = clock();
    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n"
                                                                         "time is: " << end - start << "ms\n";

    std::cout << "Boyer-Moor\n";
    start = clock();
    shift = boyer_moor(text, pattern);
    end = clock();
    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n"
                                                                         "time is: " << end - start << "ms\n";
    std::cout << "KMP\n";
    start = clock();
    shift = kmp(text, pattern);
    end = clock();
    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n"
                                                                         "time is: " << end - start << "ms\n";
    std::cout << "Rabin-Karp\n";
    start = clock();
    shift = rabin_karp(text, pattern);
    end = clock();
    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n"
                        "time is: " << end - start << "ms\n";

}
