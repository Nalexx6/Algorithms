//
// Created by Win10Pro on 2/3/2021.
//

#ifndef LAB1_IDEAL_HASH__MANUFACTURER_H
#define LAB1_IDEAL_HASH__MANUFACTURER_H

#include <iostream>
#include <string>


class Manufacturer {

private:

    int key;
    std::string name;
    std::string model;

public:

    Manufacturer(){
        this->key = -1;
    }

    Manufacturer(std::string& name, std::string& model){

        this->key = 0;
        this->name = name;
        this->model = model;

    }
    ~Manufacturer() = default;


    void setKey(const int& key) { this->key = key;}
    int getKey() {return this->key;}
    std::string getName() {return this->name;}
    std::string getModel() {return this->model;}

};


#endif //LAB1_IDEAL_HASH__MANUFACTURER_H
