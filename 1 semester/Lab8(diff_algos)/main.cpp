#include <iostream>
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

    std::string pattern = "abc", text = "sdfdfsdabcbbdddsc";

    int shift = kmp(pattern, text);

    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n";

}
