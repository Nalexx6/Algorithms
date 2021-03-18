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

private:
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
            if(toCopy == nullptr)
                return;

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
                if(parent->left != nullptr) {
                    if (parent->left->value == value) {
                        parent->left = this;
                    } else
                        parent->right = this;
                }
                else {
                    parent->right = this;
                }
            }
        }

        ~Node() = default;
    };

    void insertCase1(Node *toFix) {

//        std::cout<<"fixCase1\n";
        if (toFix->parent == nullptr)
            toFix->isBlack = true;
        else if (!toFix->parent->isBlack)
            insertCase2(toFix);

    }

    void insertCase2(Node *toFix) {

//        std::cout<<"fixCase2\n";
        Node *uncle;
        Node *gran = new Node(toFix->parent->parent);
        if(gran->parent == nullptr)
            roots[roots.size() - 1] = gran;
        Node* parent = new Node(toFix->parent);
        if (gran == nullptr)
            uncle = nullptr;
        else if (toFix->parent == gran->left) {
            if(gran->right != nullptr) {
                uncle = new Node(gran->right);
                gran->right = uncle;
            } else
                uncle = nullptr;
        }
        else {
            if(gran->left != nullptr) {
                uncle = new Node(gran->left);
                gran->left = uncle;
            }else
                uncle = nullptr;
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
            Node *savedBrother = nullptr;
            if(toFix->left != nullptr)
                savedBrother = new Node(toFix->left);

            gran->left = toFix;
            toFix->parent = gran;

            toFix->left = savedParent;
            savedParent->parent = toFix;

            savedParent->right = savedBrother;
            if(savedBrother != nullptr)
                savedParent->right->parent = savedParent;

            toFix = toFix->left;

        } else if (toFix == toFix->parent->left && toFix->parent == gran->right) {

            Node *savedParent = new Node(gran->right);
            Node *savedBrother = nullptr;
            if(toFix->right != nullptr)
               savedBrother = new Node(toFix->right);


            gran->right = toFix;
            toFix->parent = gran;

            toFix->right = savedParent;
            savedParent->parent = toFix;

            savedParent->left = savedBrother;
            if(savedBrother != nullptr)
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

    void erase(Node *node, const T &t) {
        if (node == nullptr) {
            return;
        }

        Node* copy = new Node(node);
        if(copy->parent == nullptr)
            roots.emplace_back(copy);

        if (t < node->value) {
            erase(copy->left, t);

        } else if (t > node->value) {
            erase(copy->right, t);
        } else
            deleteNode(copy);

    }

    void deleteNode(Node *toDelete) {
        if (toDelete->right == nullptr && toDelete->left == nullptr) {
            if (toDelete == roots[roots.size() - 1]) {
                roots[roots.size() - 1] == nullptr;
                return;
            }
            bool sideRight;
            Node* parent = new Node(toDelete->parent);
            if(parent->parent == nullptr)
                roots[roots.size() - 1] = parent;

            if (toDelete == toDelete->parent->right) {
                parent->right = nullptr;
                sideRight = true;
            } else {
                parent->left = nullptr;
                sideRight = false;
            }
            if (toDelete->isBlack) {
                std::cout << "balance" << std::endl;
                deleteFix(parent, sideRight);
            }

            delete toDelete;
            return;
        }
        if (toDelete->right == nullptr && toDelete->left != nullptr) {
            Node* left = new Node(toDelete->left);
            if (toDelete == roots[roots.size() - 1]) {
                roots[roots.size() - 1] = left;
                left->parent = nullptr;
                delete toDelete;
                return;
            }

            Node* parent = new Node(toDelete->parent);
            if(parent->parent == nullptr)
                roots[roots.size() - 1] = parent;

            if (toDelete == parent->right) {
                parent->right = left;
                left->parent = parent;
            } else {
                parent->left = left;
                left->parent = parent;
            }
            left->isBlack = toDelete->isBlack;
            delete toDelete;
            return;
        }
        if (toDelete->right != nullptr && toDelete->left == nullptr) {
            Node* right = new Node(toDelete->right);
            if (toDelete == roots[roots.size() - 1]) {
                roots[roots.size() - 1] = right;
                right->parent = nullptr;
                delete toDelete;
                return;
            }

            Node* parent = new Node(toDelete->parent);
            if(parent->parent == nullptr)
                roots[roots.size() - 1] = parent;

            if (toDelete == parent->right) {
                parent->right = right;
                right->parent = parent;
            } else {
                parent->left = right;
                right->parent = parent;

            }
            right->isBlack = toDelete->isBlack;
            delete toDelete;
            return;
        } else {
            Node *successor = toDelete;
            successor = new Node(successor->left);

            while (true) {
                if (successor->right != nullptr) {
                    successor = new Node(successor->right);
                } else
                    break;
            }
            toDelete->value = successor->value;
            deleteNode(successor);
            return;

        }
    }

    void deleteFix(Node *toFix, bool &sideRight) {

        Node *brother;
        if (sideRight)
            brother = new Node(toFix->left);
        else
            brother = new Node(toFix->right);

        Node *leftGrandson = brother->left;
        Node *rightGrandson = brother->right;

        if (leftGrandson == nullptr)
            leftGrandson = new Node();
        else
            leftGrandson = new Node(brother->left);

        if (rightGrandson == nullptr)
            rightGrandson = new Node();
        else
            rightGrandson = new Node(brother->right);

        if (!toFix->isBlack && brother->isBlack) {

            if (leftGrandson->isBlack && rightGrandson->isBlack) {
                std::cout << "fixCase1\n";
                toFix->isBlack = true;
                brother->isBlack = false;

            } else {
                if (sideRight) {
                    if (!leftGrandson->isBlack) {
                        std::cout << "fixCase2.1\n";
                        toFix->isBlack = true;
                        brother->isBlack = false;
                        leftGrandson->isBlack = true;
                        rightRotate(toFix);
                    } else {
                        std::cout << "fixCase2.2\n";
                        toFix->isBlack = true;

                        rightGrandson->isBlack = true;
                        leftRotate(brother);
                        rightRotate(toFix);
                    }
                } else {

                    if (!rightGrandson->isBlack) {
                        std::cout << "fixCase2.1\n";
                        toFix->isBlack = true;
                        brother->isBlack = false;
                        rightGrandson->isBlack = true;
                        leftRotate(toFix);
                    } else {
                        std::cout << "fixCase2.2\n";
                        toFix->isBlack = true;

                        leftGrandson->isBlack = true;
                        rightRotate(brother);
                        leftRotate(toFix);
                    }

                }

            }
        } else if (toFix->isBlack && !brother->isBlack) {

            Node *leftGreatGrandson;
            Node *rightGreatGrandson;

            if (sideRight) {
                leftGreatGrandson = rightGrandson->left;
                rightGreatGrandson = rightGrandson->right;
            } else {
                leftGreatGrandson = leftGrandson->left;
                rightGreatGrandson = leftGrandson->right;
            }

            if (leftGreatGrandson == nullptr) {
                leftGreatGrandson = new Node();

            } else if (sideRight)
                leftGreatGrandson = new Node(rightGrandson->left);
            else
                leftGreatGrandson = new Node(leftGrandson->left);


            if (rightGreatGrandson == nullptr) {
                rightGreatGrandson= new Node();

            } else if (sideRight)
                rightGreatGrandson = new Node(rightGrandson->right);
            else
                rightGreatGrandson = new Node(leftGrandson->right);


            if (sideRight) {
                if (leftGreatGrandson->isBlack && rightGreatGrandson->isBlack) {
                    std::cout << "fixCase3\n";
                    brother->isBlack = true;
                    rightGrandson->isBlack = false;
                    rightRotate(toFix);

                } else if (!leftGreatGrandson->isBlack) {
                    std::cout << "fixCase4\n";

                    leftRotate(brother);
                    rightRotate(toFix);
                    leftGrandson->isBlack = true;

                }
            } else {
                if (leftGreatGrandson->isBlack && rightGreatGrandson->isBlack) {
                    std::cout << "fixCase3\n";
                    brother->isBlack = true;
                    leftGrandson->isBlack = false;
                    leftRotate(toFix);

                } else if (!rightGreatGrandson->isBlack) {
                    std::cout << "fixCase4\n";

                    rightRotate(brother);
                    leftRotate(toFix);
                    rightGrandson->isBlack = true;

                }
            }


        } else {

            if (sideRight) {
//                std::cout << "fixCase5\n";
                if(!rightGrandson->isBlack) {
                    rightGrandson->isBlack = true;
                    leftRotate(brother);
                    rightRotate(toFix);
                } else if(!leftGrandson->isBlack && rightGrandson->parent == nullptr) {
                    leftGrandson->isBlack = true;
                    rightRotate(toFix);
                }
            } else if (!sideRight) {
                if(!leftGrandson->isBlack) {
                    std::cout << "fixCase5\n";
                    leftGrandson->isBlack = true;
                    rightRotate(brother);
                    leftRotate(toFix);
                } else if(!rightGrandson->isBlack && leftGrandson->parent == nullptr){
                    rightGrandson->isBlack = true;
                    leftRotate(toFix);
                }
            } else {
                std::cout << "fixCase6\n";
                brother->isBlack = false;
                if (toFix->parent != nullptr) {
                    Node* parent = new Node(toFix->parent);
                    if (toFix == parent->right)
                        sideRight = true;
                    else
                        sideRight = false;

                    deleteFix(parent, sideRight);

                }

            }

        }
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

    void erase(const T &t) {

        erase(roots[roots.size() - 1], t);

    }

    void print(){

//        for(int i = 0; i < roots.size(); i++) {
//            backupTree(roots[i], nullptr);
//            std::cout << "------------------------" << i << " version---------------------------\n";
//            print(roots[i], 0, true);
//        }

        backupTree(roots[roots.size() - 1], nullptr);
        print(roots[roots.size() - 1], 0, true);

    }

};//PersistentSet

#endif //LAB5_PERSISTENTSET__PERSISTENTSET_H
