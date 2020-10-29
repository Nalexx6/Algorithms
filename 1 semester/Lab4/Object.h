//
// Created by Win10Pro on 10/29/2020.
//

#ifndef LAB4_OBJECT_H
#define LAB4_OBJECT_H

template <typename T>
class Object {

private:
    T _element;
    int _key;

public:

    explicit Object(int key) : _key(key) {};

    ~Object() = default;

    int key() {return _key;}
    void setKey(int key) { this->_key = key;}

    T element() {return _element;}
    void setElement(T element) {this->_element = element;}

};


#endif //LAB4_OBJECT_H
