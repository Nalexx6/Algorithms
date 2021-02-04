//
// Created by Win10Pro on 2/4/2021.
//

#ifndef LAB1_IDEAL_HASH__MODEL_H
#define LAB1_IDEAL_HASH__MODEL_H

#include <iostream>
#include <string>

class Model {

    std::string name;
public:
    Model(std::string& name){
        this->name = name;
    }
    ~Model() = default;

};


#endif //LAB1_IDEAL_HASH__MODEL_H
