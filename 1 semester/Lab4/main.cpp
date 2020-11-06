
#include <random>
#include <ctime>

#include "Diff_sorts.h"

int rand(int lo, int hi) {

    static std::random_device rd;
    static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
    static std::mt19937 mt(seq);

    std::uniform_int_distribution<> range(lo, hi);

    return range(mt);

}

//#include "Object.h"
int main() {

    std::vector<Object<int>> data ;

    int n, null;
    std::cout << "Please enter the quantity of elements\n";
    std::cin >> n;
    std::cout << "Please enter the quantity of 0-elements\n";
    std::cin >> null;

//    data.reserve(n);
    for(int i = 0; i < n; i++){

        if(i < null)
            data.emplace_back((0));
        else
            data.emplace_back((1));

    }

    for(int i = 1; i < n; i++){
        std::swap(data[i], data[rand(0, i) ]);
    }

    for(int i = 0; i < data.size(); i++){

        data[i].setElement(i);

    }

//    for(int i = 0; i < n; i++){
//
//        std::cout << data[i].key() << " ";
//
//    }

//    std::vector<Object<int>> copy;
    std::cout << "\nSort\n";
    clock_t  start = clock();
//    copy = data;
//    Diff_sorts::sort_1_2(data);
//    Diff_sorts::sort_1_3(data);
    Diff_sorts::sort_2_3(data);

    clock_t end = clock();

    if(Diff_sorts::is_sorted(data))
        std::cout<< "Array was successfully sorted\n";

    if(Diff_sorts::is_stable(data))
        std::cout<< "Sort was stable\n";

    std::cout << end - start << "ms\n";


//    for(int i = 0; i < n; i++){
//
//        std::cout << data[i].key() << " ";
//
//    }
//
//    std::cout<<"\n";
//    for(int i = 0; i < n; i++){
//
//        std::cout << data[i].element() << " ";
//
//    }
}
