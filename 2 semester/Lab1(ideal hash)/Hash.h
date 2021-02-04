//
// Created by Win10Pro on 2/3/2021.
//

#ifndef LAB1_IDEAL_HASH__HASH_H
#define LAB1_IDEAL_HASH__HASH_H

#include "Manufacturer.h"

//template <typename T>

namespace gp{//general parameters for hash

    int prime = 101;

    int a = 3;
    int b = 42;


}

class Hash {

private:
    //parameters for nested hash arrays
    class Params{

    public:

        int a;
        int b;

        Params(){

            this->a = 0;
            this->b = 0;

        }

        ~Params() = default;

    };

    int capacity;
    std::vector<std::pair<std::vector<Manufacturer>, Params>> data;

    int h(const int& key) const{

        return ((gp::a * key + gp::b) % gp::prime) % this->capacity;

    }

    void auxiliaryHash(std::pair<std::vector<Manufacturer>, Params>& cell ){

        std::vector<int> positions (cell.first.size(), 0);
        std::vector<Manufacturer> updatedCell (cell.first.size() * cell.first.size());


        for (int a = 0; a < gp::prime; ++a) {

            for (int b = 0; b < gp::prime - 1 ; ++b) {

                for (int i = 0; i < positions.size(); ++i) {

                    positions[i] = hParam(cell.first[i].getKey(), a, b, updatedCell.size());

                }
                if(collisionCheck(positions)){

                    cell.second.a = a;
                    cell.second.b = b;

                    for (int i = 0; i < positions.size(); ++i) {

                        updatedCell[positions[i]] = cell.first[i];


                    }

                    cell.first = updatedCell;
                    return;

                }

            }

        }

    }

    int hParam(const int& key, int& a, int& b, const int& size){

        return ((a * key + b) % gp::prime) % size;


    }

    bool collisionCheck(const std::vector<int>& positions){

        std::vector<bool> array (gp::prime, false);

        for(auto& i: positions){

            if(array[i])
                return false;

            array[i] = true;
        }

        return true;
    }

public:

    explicit Hash(std::vector<Manufacturer>& input){

        this->capacity = input.size();
        data.resize(capacity);
        int position;

        for(auto& i: data){

            i = std::pair(std::vector<Manufacturer>{}, Params());

        }

        for(auto& i: input){

            position = h(i.getKey());
            std::cout << position << " ";
            data[position].first.emplace_back(i);

        }

        for(auto& i: data){

            if(i.first.size() > 1) {
                    auxiliaryHash(i);
            }

        }

    }

    Manufacturer get(const int& key){

        std::pair<std::vector<Manufacturer>, Params>& cell = data[h(key)];
        return cell.first[hParam(key, cell.second.a, cell.second.b, cell.first.size())];

    }

    void print(){

        for(auto& i: data){

            std::cout << i.first.size() << " " << i.second.a << " " << i.second.b << " || ";

            for(auto& j : i.first){

                std::cout << j.getKey() << " " << j.getName() << " ";

            }

            std::cout << std::endl;
        }

    }

};


#endif //LAB1_IDEAL_HASH__HASH_H
