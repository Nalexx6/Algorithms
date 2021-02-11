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

    void fixCase1(Node* toFix){

        if(toFix->parent == nullptr)
            this->root->isBlack = true;
        else if(!toFix->parent->isBlack)
            fixCase2(toFix);

    }

    void fixCase2(Node* toFix){

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
            fixCase1(gran);
        } else
            fixCase3(toFix);

    }

    void fixCase3(Node* toFix){

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

        fixCase4(toFix);
    }

    void fixCase4(Node* toFix){

        Node* gran = toFix->parent->parent;

        toFix->parent->isBlack = true;
        gran->isBlack = false;

        if(toFix == toFix->parent->left && toFix->parent == gran->left)
            rightRotate(gran);
        else
            leftRotate(gran);

    }
    void leftRotate(Node* toRotate){

        Node* pivot = toRotate->right;

        pivot->parent = toRotate->parent;
        if(toRotate->parent != nullptr)
            if (toRotate->parent->left == toRotate)
                toRotate->parent->left = pivot;
            else
                toRotate->parent->right = pivot;


        toRotate->right = pivot->left;
        if(pivot->left != nullptr)
            pivot->left->parent = toRotate;

        toRotate->parent = pivot;
        pivot->left = toRotate;

    }
    void rightRotate(Node* toRotate){

        Node* pivot = toRotate->left;

        pivot->parent = toRotate->parent;
        if(toRotate->parent != nullptr)
            if (toRotate->parent->left == toRotate)
                toRotate->parent->left = pivot;
            else
                toRotate->parent->right = pivot;


        toRotate->right = pivot->right;
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

        fixCase1(toInsert);
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

        if(node == this->root)
            std::cout << node->value << " " << node->isBlack << "\n";
        else
            std::cout << node->value << " " << node->isBlack << " " << node->parent->value << "\n";

    }


};


#endif //LAB2_ORDERSTATTREE__TREE_H
