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
        explicit Node(T& value){
            this->value = value;
            left = right = parent = nullptr;
        }

        ~Node() = default;
    };


    Node* root;

    void splay(Node* toSplay, Node* rootSplay){

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
        }

        if(parent == nullptr)
            this->root == toSplay;

    }

    void zig(Node* toSplay, bool leftSide){

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

        if(toSplay->parent != nullptr)
            if(parent == toSplay->parent->left)
                toSplay->parent->left = toSplay;
            else
                toSplay->parent->right = toSplay;


        parent->parent = toSplay;


    }

    void zigZig(Node* toSplay, bool leftSide){

        Node* parent = toSplay->parent;
        Node* gran = parent->parent;

        if(leftSide){

            gran->left = parent->right;
            if(parent->right != nullptr)
                gran->left->parent = gran;

            parent->left = toSplay->right;
            if(toSplay->right != nullptr)
                parent->left->parent = parent;

        } else{

            gran->right = parent->left;
            if(parent->left != nullptr)
                gran->right->parent = gran;

            parent->right = toSplay->left;
            if(toSplay->left != nullptr)
                parent->right->parent = parent;

        }

        if(gran->parent != nullptr){
            toSplay->parent = gran->parent;
            if(gran == gran->parent->left)
                gran->parent->left = toSplay;
            else
                gran->parent->right = toSplay;
        }
        gran->parent = parent;
        parent->parent = toSplay;

    }

    void zigZag(Node* toSplay, bool leftSide){

        Node* parent = toSplay->parent;
        Node* gran = parent->parent;

        if(leftSide){

            parent->right = toSplay->left;
            if(toSplay->left != nullptr)
                parent->right->parent = parent;

            gran->left = toSplay->right;
            if(toSplay->right != nullptr)
                gran->left->parent = parent;

            toSplay->left = parent;
            toSplay->right = gran;
            parent->parent = toSplay;
            gran->parent = toSplay;

        } else{

            parent->left = toSplay->right;
            if(toSplay->right != nullptr)
                parent->left->parent = parent;

            gran->right = toSplay->left;
            if(toSplay->left != nullptr)
                gran->right->parent = parent;

            toSplay->right = parent;
            toSplay->left = gran;
            parent->parent = toSplay;
            gran->parent = toSplay;

        }

        if(gran->parent != nullptr){
            toSplay->parent = gran->parent;
            if(gran == gran->parent->left)
                gran->parent->left = toSplay;
            else
                gran->parent->right = toSplay;
        }
        gran->parent = parent;
        parent->parent = toSplay;

    }

    void merge(){



    }

    void split(){

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

    void print(Node* node, int level) const{

        if(node == nullptr)
            return;


        if(node == this->root) {
            std::cout << node->value << std::endl;

        }
        else {
            for(int i = 0; i < level; i++){

                std::cout<<"|\t";

            }
            std::cout << node->value;
            std::cout << "parent " <<  node->parent->value << "\n";
        }

        print(node->left, level + 1);

        print(node->right, level + 1);

    }

public:

    SplayTree(){

        this->root == nullptr;

    }

    void insert(T& t){



    }
    void erase(T& t){



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

        print(this->root, 0);

    }




};