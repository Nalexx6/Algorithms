//
// Created by Win10Pro on 2/3/2021.
//

#ifndef LAB1_IDEAL_HASH__MANUFACTURER_H
#define LAB1_IDEAL_HASH__MANUFACTURER_H

#include "Model.h"
#include <vector>

class Manufacturer {

private:

    int key;
    std::string name;
    std::vector<Model> models;

public:

    Manufacturer(){
        this->key = -1;
    }

    Manufacturer(int& key, std::string& name){

        this->key = key;
        this->name = name;

    }
    ~Manufacturer() = default;

    int getKey() {return this->key;}
    std::string getName() {return this->name;}
    std::vector<Model> getModels() {return this->models;}

};


#endif //LAB1_IDEAL_HASH__MANUFACTURER_H
