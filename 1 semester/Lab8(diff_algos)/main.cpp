#include <iostream>
#include "Algoritms/KMP.h"

int main() {

    std::string pattern = "abc", text = "sdfdfsdabcbbdd;dsc";

    int shift = kmp(pattern, text);

    if(shift != -1)
        std::cout << "Pattern was found in text, shift is: " << shift << " symbols\n";

}
