#include "Hash.h"

int main() {

    std::vector<std::string> manufacturers {"Ford", "Ferrari", "Lambo", "Toyota", "Tesla", "Fiat",
                                            "Renault", "BMW", "Mercedes", "Honda"};
    std::vector<std::string> models{"Mustang", "Spider", "Aventador", "Land Cruiser", "ModelX", "Doblo",
                                            "Logan", "X6", "Sprinter", "Sonata"};
    int size = 10, key;
    std::vector<Manufacturer> input;

    for(int i = 0; i < size; i++){

//        key = rand() % gp::prime;
        input.emplace_back(manufacturers[i], models[i]);

    }

    Hash* hash = new Hash(input);
    hash->print();

    std::cout << "Element with key = " << 85 << " has name " << hash->get(models[0]).getName();
}
