//
// Created by Win10Pro on 3/16/2021.
//

#ifndef LAB5_PERSISTENTSET__PERSISTENTSET_H
#define LAB5_PERSISTENTSET__PERSISTENTSET_H

#include <iostream>
#include <vector>

/*
 * Class implements persistent set based on red-black tree
 * time of insertion, deletion and needed memory - O(log n) in worst case
 */

template <typename T>
class PersistentSet{

    class Node {

    public:
        T value;
        Node *parent;
        Node *left;
        Node *right;
        bool isBlack{};

        Node() {
            left = right = parent = nullptr;
            isBlack = true;
        }

        explicit Node(T &value){
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->isBlack = false;
        }

        Node(Node* toCopy) {
            this->value = toCopy->value;
            this->left = toCopy->left;
            this->right = toCopy->right;
            this->parent = toCopy->parent;
            this->isBlack = toCopy->isBlack;


            if (left != nullptr)
                left->parent = this;
            if (right != nullptr)
                right->parent = this;

            if (parent != nullptr) {
                if (parent->left->value == value)
                    parent->left = this;
                else
                    parent->right = this;
            }
        }

        ~Node() = default;
    };

    void insertCase1(Node *toFix) {

        std::cout<<"fixCase1\n";
        if (toFix->parent == nullptr)
            toFix->isBlack = true;
        else if (!toFix->parent->isBlack)
            insertCase2(toFix);

    }

    void insertCase2(Node *toFix) {

        std::cout<<"fixCase2\n";
        Node *uncle;
        Node *gran = new Node(toFix->parent->parent);
        if(gran->parent == nullptr)
            roots[roots.size() - 1] = gran;
        Node* parent = new Node(toFix->parent);
        if(parent->parent == gran)
            std::cout<<"dffsds\n";
        if(gran->left == parent)
            std::cout<<"dffsds\n";
        if (gran == nullptr)
            uncle = nullptr;
        else if (toFix->parent == gran->left) {
            uncle = new Node(gran->right);
            gran->right = uncle;
        }
        else {
            uncle = new Node(gran->left);
            gran->left = uncle;
        }

        if (uncle != nullptr && !uncle->isBlack) {
            gran->isBlack = false;
            parent->isBlack = true;
            uncle->isBlack = true;
            insertCase1(gran);
        } else
            insertCase3(toFix);

    }

    void insertCase3(Node *toFix) {

        std::cout<<"fixCase3\n";
        Node *gran = new Node(toFix->parent->parent);
        if(gran->parent == nullptr)
            roots[roots.size() - 1] = gran;

        if (toFix == toFix->parent->right && toFix->parent == gran->left) {

            Node *savedParent = new Node(gran->left);
            Node *savedBrother = new Node(toFix->left);

            gran->left = toFix;
            toFix->parent = gran;

            toFix->left = savedParent;
            savedParent->parent = toFix;

            savedParent->right = savedBrother;
            savedParent->right->parent = savedParent;

            toFix = toFix->left;

        } else if (toFix == toFix->parent->left && toFix->parent == gran->right) {

            Node *savedParent = new Node(gran->right);
            Node *savedBrother = new Node(toFix->right);

            gran->right = toFix;
            toFix->parent = gran;

            toFix->right = savedParent;
            savedParent->parent = toFix;

            savedParent->left = savedBrother;
            savedParent->left->parent = savedParent;

            toFix = toFix->right;

        }

        insertCase4(toFix);
    }

    void insertCase4(Node *toFix) {

        std::cout<<"fixCase4\n";
        Node *gran = new Node(toFix->parent->parent);
        if(gran->parent == nullptr)
            roots[roots.size() - 1] = gran;
        Node *parent = new Node(toFix->parent);

        parent->isBlack = true;
        gran->isBlack = false;

        if (toFix == toFix->parent->left && toFix->parent == gran->left)
            rightRotate(gran);
        else
            leftRotate(gran);

    }

    void leftRotate(Node *toRotate) {

//        std::cout<<"leftRotate\n";

        Node *pivot = new Node(toRotate->right);

        pivot->parent = toRotate->parent;

        if (toRotate->parent != nullptr) {
            if (toRotate->parent->left == toRotate) {
                toRotate->parent->left = pivot;
            } else {
                toRotate->parent->right = pivot;
            }
        } else
            this->roots[roots.size() - 1] = pivot;

        toRotate->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = toRotate;

        toRotate->parent = pivot;
        pivot->left = toRotate;

    }

    void rightRotate(Node *toRotate) {

//        std::cout<<"rightRotate\n";
        Node *pivot = new Node(toRotate->left);

        pivot->parent = toRotate->parent;
        if (toRotate->parent != nullptr)
            if (toRotate->parent->left == toRotate)
                toRotate->parent->left = pivot;
            else
                toRotate->parent->right = pivot;
        else
            this->roots[roots.size() - 1] = pivot;

        toRotate->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = toRotate;

        toRotate->parent = pivot;
        pivot->right = toRotate;

    }

    void backupTree(Node* toBackup, Node* parent){

        if(toBackup == nullptr)
            return;

        toBackup->parent = parent;

        backupTree(toBackup->left, toBackup);
        backupTree(toBackup->right, toBackup);

    }

    void print(Node *node, int level, bool left) const {

        if (node == nullptr)
            return;


        if (node->parent == nullptr) {
            std::cout << node->value << " " ;
            if (node->isBlack)
                std::cout << " Black\n";
            else
                std::cout << " Red\n";
        } else {
            for (int i = 0; i < level; i++) {

                std::cout << "|\t";

            }
            std::cout << node->value << " ";

            if(left)
                std::cout << "LEFT ";
            else
                std::cout << "RIGHT ";

            if (node->isBlack)
                std::cout << "Black ";
            else
                std::cout << "Red ";

            std::cout << "parent " << node->parent->value << "\n";
        }

        print(node->right, level + 1, false);
        print(node->left, level + 1, true);

    }

    std::vector<Node*> roots;

public:

    PersistentSet(){
        roots = {nullptr};
    }

    void insert(T& t){

//        if(roots.empty()) {
//            roots.push_back(new Node(t, nullptr, nullptr, nullptr));
//            return;
//        }

        Node* temp = roots[roots.size() - 1];

        Node *futureParent = nullptr;
        Node *toInsert = new Node(t);

        while (temp != nullptr) {

            futureParent = new Node(temp);
            if(futureParent->parent == nullptr)
                roots.emplace_back(futureParent);

            if (toInsert->value < temp->value) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }

        toInsert->parent = futureParent;

        if (futureParent == nullptr) {
            roots.emplace_back(toInsert);
        }
        else if (toInsert->value < futureParent->value)
            futureParent->left = toInsert;
        else
            futureParent->right = toInsert;

        insertCase1(toInsert);

    }

    void print(){

//        for(int i = roots.size(); i < roots.size(); i++) {
//            backupTree(roots[i], nullptr);
//            std::cout << "------------------------" << i << " version---------------------------\n";
//            print(roots[i], 0, true);
//        }

        backupTree(roots[roots.size() - 1], nullptr);
        print(roots[roots.size() - 1], 0, true);

    }

};//PersistentSet

#endif //LAB5_PERSISTENTSET__PERSISTENTSET_H
