//
// Created by Win10Pro on 2/11/2021.
//

#ifndef LAB2_ORDERSTATTREE__TREE_H
#define LAB2_ORDERSTATTREE__TREE_H

#include "Manufacturer.h"

template <typename T>
class Tree {

private:
    class Node{

    public:
        T value;
        Node* parent;
        Node* left;
        Node* right;
//        bool isLeftSon;
        bool isBlack;


        explicit Node(T& value){
            this->value = value;
            left = right = parent = nullptr;
            isBlack = false;
//            isLeftSon = true;
        }

        ~Node() = default;
    };

    Node* root;

    void insertCase1(Node* toFix){

//        std::cout<<"fixCase1\n";
        if(toFix->parent == nullptr)
            this->root->isBlack = true;
        else if(!toFix->parent->isBlack)
            insertCase2(toFix);

    }

    void insertCase2(Node* toFix){

//        std::cout<<"fixCase2\n";
        Node* uncle;
        Node* gran = toFix->parent->parent;
        if(gran == nullptr)
            uncle = nullptr;
        else if(toFix->parent == gran->left)
            uncle = gran->right;
        else
            uncle = gran->left;

        if(uncle != nullptr && !uncle->isBlack){
            toFix->parent->isBlack = true;
            uncle->isBlack = true;
            gran->isBlack = false;
            insertCase1(gran);
        } else
            insertCase3(toFix);

    }

    void insertCase3(Node* toFix){

//        std::cout<<"fixCase3\n";
        Node* gran = toFix->parent->parent;
        if(toFix == toFix->parent->right && toFix->parent == gran->left){

            Node* savedParent = gran->left;
            Node* savedBrother = toFix->parent->left;

            gran->left = toFix;
            toFix->left = savedParent;
            savedParent->right = savedBrother;
            toFix = toFix->left;

        } else if(toFix == toFix->parent->left && toFix->parent == gran->right){

            Node* savedParent = gran->right;
            Node* savedBrother = toFix->parent->right;

            gran->right = toFix;
            toFix->right = savedParent;
            savedParent->left = savedBrother;
            toFix = toFix->right;

        }

        insertCase4(toFix);
    }

    void insertCase4(Node* toFix){

//        std::cout<<"fixCase4\n";
        Node* gran = toFix->parent->parent;

        toFix->parent->isBlack = true;
        gran->isBlack = false;

        if(toFix == toFix->parent->left && toFix->parent == gran->left)
            rightRotate(gran);
        else
            leftRotate(gran);

    }

    void leftRotate(Node* toRotate){

        std::cout<<"leftRotate\n";

        Node* pivot = toRotate->right;

        pivot->parent = toRotate->parent;

        if(toRotate->parent != nullptr) {
            if (toRotate->parent->left == toRotate) {
                toRotate->parent->left = pivot;
            } else {
                toRotate->parent->right = pivot;
            }
        }
        else
            this->root = pivot;

        toRotate->right = pivot->left;
        if(pivot->left != nullptr)
            pivot->left->parent = toRotate;

        toRotate->parent = pivot;
        pivot->left = toRotate;

    }
    void rightRotate(Node* toRotate){

        std::cout<<"rightRotate\n";
        Node* pivot = toRotate->left;

        pivot->parent = toRotate->parent;
        if(toRotate->parent != nullptr)
            if (toRotate->parent->left == toRotate)
                toRotate->parent->left = pivot;
            else
                toRotate->parent->right = pivot;
        else
            this->root = pivot;

        toRotate->left = pivot->right;
        if(pivot->right!= nullptr)
            pivot->right->parent = toRotate;

        toRotate->parent = pivot;
        pivot->right = toRotate;

    }

public:

    int size;

    Tree(){

        this->root = nullptr;
        size = 0;

    }

    void insert(T& t){

        Node* temp = root;
        Node* futureParent = nullptr;
        Node* toInsert = new Node(t);

        while (temp != nullptr){

            futureParent = temp;

            if(toInsert->value < temp->value)
                temp = temp->left;
            else
                temp = temp->right;

        }

        toInsert->parent = futureParent;

        if(futureParent == nullptr)
            this->root = toInsert;
        else if(toInsert->value < futureParent->value)
            futureParent->left = toInsert;
        else
            futureParent->right = toInsert;

        insertCase1(toInsert);
        size++;
    }

    void print(){

        print(this->root);

    }
    void print(Node* node){

        if(node == nullptr)
            return;

        print(node->left);

        print(node->right);

        if(node == this->root) {
            std::cout << node->value << " ";
            if(node->isBlack)
                std::cout<< "Black\n";
            else
                std::cout<< "Red\n";
        }
        else {
            std::cout << node->value << " ";

            if (node->isBlack)
                std::cout << "Black ";
            else
                std::cout << "Red ";

            std::cout << node->parent->value << "\n";
        }

    }


};


#endif //LAB2_ORDERSTATTREE__TREE_H
