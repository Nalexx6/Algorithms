
#include "Sort.h"


int main() {

    int quantity;
    std::cout<<"Please enter the quantity of bolts and nuts\n";
    std::cin>>quantity;

    std::vector<int> bolts;
    std::vector<int> nuts;

    for(int i = 0; i < quantity; i++){

        bolts.emplace_back(i);
        nuts.emplace_back(i);

    }

    Sort::shuffle(bolts, 0, quantity - 1);
    Sort::shuffle(nuts, 0, quantity);


}
