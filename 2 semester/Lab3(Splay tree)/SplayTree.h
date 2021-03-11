//
// Created by Win10Pro on 2/24/2021.
//

#ifndef LAB3_SPLAY_TREE__SPLAYTREE_H
#define LAB3_SPLAY_TREE__SPLAYTREE_H

#endif //LAB3_SPLAY_TREE__SPLAYTREE_H

#include <iostream>

template <typename T>
class SplayTree {

private:

    class Node{

    public:
        T value;
        Node* parent;
        Node* left;
        Node* right;

        Node() {
            left = right = parent = nullptr;
        }
        explicit Node(const T& value){
            this->value = value;
            left = right = parent = nullptr;
        }

        ~Node() = default;
    };


    Node* root;

    void splay(Node* toSplay, Node* rootSplay){

        std::cout << "toSplay = " << toSplay->value << std::endl;
        std::cout << "rootSplay = " << rootSplay->value << std::endl;
        Node* parent = rootSplay->parent;
        while (toSplay->parent != parent){
            if(toSplay->parent->parent == nullptr)
                if(toSplay == toSplay->parent->left)
                    zig(toSplay, true);
                else
                    zig(toSplay, false);
            else
                if(toSplay == toSplay->parent->left)
                    if(toSplay->parent == toSplay->parent->parent->left)
                        zigZig(toSplay, true);
                    else
                        zigZag(toSplay, false);
                else
                    if(toSplay->parent == toSplay->parent->parent->right)
                        zigZig(toSplay, false);
                    else
                        zigZag(toSplay, true);

//            print();
        }

        if(parent == nullptr) {
            this->root = toSplay;
        }

    }

    void zig(Node* toSplay, bool leftSide){
        std::cout<<"Zig" << std::endl;

        Node* parent = toSplay->parent;
        if(leftSide){

            parent->left = toSplay->right;
            if(toSplay->right != nullptr)
                parent->left->parent = parent;

            toSplay->right = parent;

        } else{

            parent->right = toSplay->left;
            if(toSplay->left != nullptr)
                parent->right->parent = parent;

            toSplay->left = parent;

        }

        toSplay->parent = parent->parent;

        if(toSplay->parent != nullptr) {
            if (parent == toSplay->parent->left) {
                toSplay->parent->left = toSplay;
            } else {
                toSplay->parent->right = toSplay;
            }
        }

        parent->parent = toSplay;


    }

    void zigZig(Node* toSplay, bool leftSide){

        std::cout<<"Zigzig" << std::endl;
        Node* parent = toSplay->parent;
        Node* gran = parent->parent;

        if(leftSide){

            gran->left = parent->right;
            if(parent->right != nullptr)
                gran->left->parent = gran;

            parent->left = toSplay->right;
            if(toSplay->right != nullptr)
                parent->left->parent = parent;

            parent->right = gran;
            toSplay->right = parent;

        } else{

            gran->right = parent->left;
            if(parent->left != nullptr)
                gran->right->parent = gran;

            parent->right = toSplay->left;
            if(toSplay->left != nullptr)
                parent->right->parent = parent;

            parent->left = gran;
            toSplay->left = parent;

        }

        toSplay->parent = gran->parent;
        if(gran->parent != nullptr){
            if(gran == gran->parent->left)
                gran->parent->left = toSplay;
            else
                gran->parent->right = toSplay;
        }

        gran->parent = parent;
        parent->parent = toSplay;

    }

    void zigZag(Node* toSplay, bool leftSide){
        std::cout<<"Zigzag" << std::endl;

        Node* parent = toSplay->parent;
        Node* gran = parent->parent;

        if(leftSide){

            parent->right = toSplay->left;
            if(toSplay->left != nullptr)
                parent->right->parent = parent;

            gran->left = toSplay->right;
            if(toSplay->right != nullptr)
                gran->left->parent = gran;

            toSplay->left = parent;
            toSplay->right = gran;
            parent->parent = toSplay;

        } else{

            parent->left = toSplay->right;
            if(toSplay->right != nullptr)
                parent->left->parent = parent;

            gran->right = toSplay->left;
            if(toSplay->left != nullptr)
                gran->right->parent = gran;

            toSplay->right = parent;
            toSplay->left = gran;
            parent->parent = toSplay;

        }

        toSplay->parent = gran->parent;
        if(gran->parent != nullptr){
            if(gran == gran->parent->left)
                gran->parent->left = toSplay;
            else
                gran->parent->right = toSplay;
        }
        gran->parent = toSplay;
        parent->parent = toSplay;

    }

    void merge(Node* rootLeft, Node* rootRight){

        if(rootLeft == nullptr && rootRight == nullptr){
            this->root = nullptr;
            return;
        }
        if(rootLeft == nullptr){
            this->root = rootRight;
            return;
        }
        if(rootRight == nullptr){

            this->root = rootLeft;
            return;
        }

        Node* maxLeft = rootLeft->right;

        if(maxLeft == nullptr) {
            rootLeft->right = rootRight;
            rootRight->parent = rootLeft;
            this->root = rootLeft;
            return;
        }

        while (maxLeft->right != nullptr){

            maxLeft = maxLeft->right;

        }

        splay(maxLeft, rootLeft);


        maxLeft->right = rootRight;
        rootRight->parent = maxLeft;
        this->root = maxLeft;

    }

    void split(const T& t){

        Node* successor;
        Node* temp = this->root;

        while(temp != nullptr){
//            std::cout<<"dfdfd\n";
            if(temp->value == t) {
                successor = temp;
                break;
            }
            if(temp->value > t) {
                successor = temp;
                temp = temp->left;
            } else
                temp = temp->right;
        }

        splay(successor, this->root);

        Node* toInsert = new Node(t);
        if(successor->value >= toInsert->value) {

            toInsert->left = successor->left;
            if (toInsert->left != nullptr)
                toInsert->left->parent = toInsert;
            successor->left = nullptr;
            toInsert->right = successor;

        } else
            toInsert->left = successor;

        successor->parent = toInsert;
        this->root = toInsert;

    }



    Node* erase(Node* node, const T& t) {
        if (node == nullptr) {
            return nullptr;
        }

        if (t < node->value) {
            return erase(node->left, t);

        }
        else if (t > node->value) {
            return erase(node->right, t);
        }
        else
            return node;

    }

    Node* get(Node* node, const T& t){

        if(node == nullptr)
            return nullptr;

        if(t == node->value)
            return node;

        if(t < node->value)
            return get(node->left, t);
        else
            return get(node->right, t);

    }

    void print(Node* node, int level, bool left) const{

        if(node == nullptr)
            return;


        if(node == this->root) {
            std::cout << node->value << std::endl;

        }
        else {
            for(int i = 0; i < level; i++){

                std::cout<<"|\t";

            }
            if(left)
                std::cout << "LEFT ";
            else
                std::cout << "RIGHT ";
            std::cout << node->value;
            std::cout << " parent " <<  node->parent->value << "\n";
        }

        print(node->left, level + 1, true);

        print(node->right, level + 1, false);

    }

public:

    SplayTree(){

        this->root = nullptr;

    }
    ~SplayTree() = default;

    void insert(T& t){

        if(this->root == nullptr){
//            std::cout<<"no root"<< std::endl;
            this->root = new Node(t);
            return;
        } else
            split(t);

    }
    void erase(const T& t){

//        std::string  breakpoint;
        Node* toDelete = erase(this->root, t);
        std::cout << toDelete->value << std::endl;
        splay(toDelete, this->root);
//        std::cout<< "--------------splayed---------" <<std::endl;
//        print(this->root, 0, true);
//        std::cin>>breakpoint;
        merge(this->root->left, this->root->right);
        if(this->root != nullptr)
            this->root->parent = nullptr;

    }
    T get(T& t){

        Node* res = get(this->root, t);

        if(res != nullptr) {
            splay(res, this->root);
            return res->value;
        } else
            return T();

    }

    void print(){

        print(this->root, 0, true);

    }




};