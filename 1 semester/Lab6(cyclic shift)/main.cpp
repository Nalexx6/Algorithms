#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefix(const std::string& a){

    std::vector<int> result;

    result.emplace_back(0);
    int k;

    for(int i = 1; i < a.length(); i++){

        k = result[i - 1];
        std::cout <<k <<"\n";

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

            std::cout << "fdsf\n";
        }

    }

   return result;

}

int check_shift(std::string& a, std::string& b){

    std::vector<int> prefixes = prefix(a);

    for(auto i: prefixes)
        std::cout<<i<<" ";
    std::cout<<"\n";

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

int main() {

    std::string a, b;

    std::cin >> a >> b;

    if(a.size() != b.size()) {
        std::cout << "No";
        return 1;
    }

    int shift = check_shift(a, b);

    if(shift == -1) {
        std::cout << "No";
        return 1;
    }

    std::cout << "Yes, shift was done by " << shift << " symbols\n";

    return 0;
}
