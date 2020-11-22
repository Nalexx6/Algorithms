#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int q = 31;//main simple integer for algorithm
const int size = 100;//approximate quantity of possible symbols(95 if not round)
int h;



int hash(std::string& a){

    int res = 0;
    for(int i = 0; i < a.size(); i++){

        res = (res * size + a[i]) % q;

    }

    return res;

}

bool check(std::vector<std::string>& text, std::vector<std::string>& pattern, std::vector<int>& hpattern, std::vector<int>& htext,
           int i_pos, int j_pos){

    for(int i = 0; i < hpattern.size(); i++){

        if(hpattern[i] != htext[i])
            return false;


    }

    for(int i = 0; i < pattern.size(); i++){

        for(int j = 0; j < pattern.size(); j++){

            if(pattern[i][j] != text[i_pos + i][j_pos + j])
                return false;

        }

    }

    return true;

}

std::pair<int, int> rabin_karp(std::vector<std::string>& text, std::vector<std::string>& pattern){


    std::vector<int> hpattern;
    hpattern.reserve(pattern.size());

    for(int i = 0; i < pattern.size(); i++) {
        hpattern.push_back(hash(pattern[i]));
        std::cout << hpattern[i] << "\n";
    }

    std::cout << "ffdf\n";

    std::vector<int> htext;

    std::string temp;

    for(int i = 0; i < text.size() - pattern.size() + 1; i++){

        for(int k = i; k < i +  pattern.size(); k++){

            for(int j = 0; j < pattern.size(); j++){

                temp+= text[k][j];

            }

            htext.emplace_back(hash(temp));
            temp = "";
            std::cout << htext[k - i] << "\n";

        }
        std::cout << "lala\n";


        for(int j = 0; j < text.size() - pattern.size() + 1; j++){

            if(check(text, pattern, hpattern, htext, i, j))
                return std::pair<int, int> (i, j);

            else{

                for(int k = 0; k < htext.size(); k++){

                    htext[k] = ((htext[k] + text[i + k][j] * (q - h % q)) * size + text[i + k][j + pattern.size()]) % q;
                    std::cout << htext[k] << "\n";


                }
                std::cout << "lol\n";


            }

        }

        htext.clear();

    }

    return std::pair<int, int> (-1, -1);

}

int main() {


    std::vector<std::string> text, pattern;

    int m, n;

    std::cout << "Please, enter size of text\n";
    std::cin >> n;

    std::cout << "Please, enter size of pattern\n";
    std::cin >> m;


    std::cout <<"Please enter " << n << " strings with length = " << n << " as your text\n";
    std::string temp;
    for(int i = 0; i < n; i++){

        std::cin >> temp;
        if(temp.size() == n)
            text.emplace_back(temp);
        else{
            std::cout << "String is inappropriate, " << n - i <<" strings to enter\n";
            i--;
        }

    }

    std::cout <<"Please enter " << m << " strings with length = " << m << " as your pattern\n";
    for(int i = 0; i < m; i++){

        std::cin >> temp;
        if(temp.size() == m)
            pattern.emplace_back(temp);
        else{
            std::cout << "String is inappropriate, " << m - i <<" strings to enter\n";
            i--;
        }

    }

    h = pow(size, m - 1);
    std::cout << "h = " << h << "\n";

    std::pair<int, int> shift = rabin_karp(text, pattern);

    if(shift.first == -1){

        std::cout << "No coincidences\n";
        return 1;

    }

    std::cout << "Coincidence found. Shift was done by " << shift.first << " symbolds down and " << shift.second <<
                " symbols right\n";

    return 0;
}
