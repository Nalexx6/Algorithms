//
// Created by Win10Pro on 2/11/2021.
//

#ifndef LAB2_ORDERSTATTREE__TREE_H
#define LAB2_ORDERSTATTREE__TREE_H

#include "Manufacturer.h"

template <typename T>
class Tree {

private:
    class Node {

    public:
        T value;
        Node *parent;
        Node *left;
        Node *right;
        bool isBlack;
        int size;


        Node() {
            left = right = parent = nullptr;
            isBlack = true;
            size = 1;
        }

        explicit Node(T &value) {
            this->value = value;
            left = right = parent = nullptr;
            isBlack = false;
            size = 1;
        }

        ~Node() = default;
    };

    Node *root;

    int getSize(Node *node) const {
        if (node == nullptr)
            return 0;

        return node->size;
    }

    void insertCase1(Node *toFix) {

//        std::cout<<"fixCase1\n";
        if (toFix->parent == nullptr)
            this->root->isBlack = true;
        else if (!toFix->parent->isBlack)
            insertCase2(toFix);

    }

    void insertCase2(Node *toFix) {

//        std::cout<<"fixCase2\n";
        Node *uncle;
        Node *gran = toFix->parent->parent;
        if (gran == nullptr)
            uncle = nullptr;
        else if (toFix->parent == gran->left)
            uncle = gran->right;
        else
            uncle = gran->left;

        if (uncle != nullptr && !uncle->isBlack) {
            toFix->parent->isBlack = true;
            uncle->isBlack = true;
            gran->isBlack = false;
            insertCase1(gran);
        } else
            insertCase3(toFix);

    }

    void insertCase3(Node *toFix) {

        std::cout<<"fixCase3\n";
        Node *gran = toFix->parent->parent;
        if (toFix == toFix->parent->right && toFix->parent == gran->left) {

            Node *savedParent = gran->left;
            Node *savedBrother = toFix->left;

            gran->left = toFix;
            toFix->parent = gran;

            toFix->left = savedParent;
            savedParent->parent = toFix;

            savedParent->right = savedBrother;
            if(savedBrother != nullptr)
                savedParent->right->parent = savedParent;

            toFix = toFix->left;

        } else if (toFix == toFix->parent->left && toFix->parent == gran->right) {

            Node *savedParent = gran->right;
            Node *savedBrother = toFix->right;

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
        Node *gran = toFix->parent->parent;

        toFix->parent->isBlack = true;
        gran->isBlack = false;

        if (toFix == toFix->parent->left && toFix->parent == gran->left)
            rightRotate(gran);
        else
            leftRotate(gran);

    }

    void leftRotate(Node *toRotate) {

//        std::cout<<"leftRotate\n";

        Node *pivot = toRotate->right;

        pivot->parent = toRotate->parent;

        if (toRotate->parent != nullptr) {
            if (toRotate->parent->left == toRotate) {
                toRotate->parent->left = pivot;
            } else {
                toRotate->parent->right = pivot;
            }
        } else
            this->root = pivot;

        toRotate->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = toRotate;

        toRotate->parent = pivot;
        pivot->left = toRotate;

        pivot->size = getSize(toRotate);
        toRotate->size = getSize(toRotate->left) + getSize(toRotate->right) + 1;


    }

    void rightRotate(Node *toRotate) {

//        std::cout<<"rightRotate\n";
        Node *pivot = toRotate->left;

        pivot->parent = toRotate->parent;
        if (toRotate->parent != nullptr)
            if (toRotate->parent->left == toRotate)
                toRotate->parent->left = pivot;
            else
                toRotate->parent->right = pivot;
        else
            this->root = pivot;

        toRotate->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = toRotate;

        toRotate->parent = pivot;
        pivot->right = toRotate;

        pivot->size = getSize(toRotate);
        toRotate->size = getSize(toRotate->left) + getSize(toRotate->right) + 1;

    }

    void erase(Node *node, const T &t) {
        if (node == nullptr) {
            return;
        }

        node->size--;

        if (t < node->value) {
            erase(node->left, t);

        } else if (t > node->value) {
            erase(node->right, t);
        } else
            deleteNode(node);

    }

    void deleteNode(Node *toDelete) {
        if (toDelete->right == nullptr && toDelete->left == nullptr) {
            if (toDelete == root) {
                root == nullptr;
                return;
            }
            bool sideRight;
            if (toDelete == toDelete->parent->right) {
                toDelete->parent->right = nullptr;
                sideRight = true;
            } else {
                toDelete->parent->left = nullptr;
                sideRight = false;
            }
//            toDelete->parent->size--;
            if (toDelete->isBlack) {
                std::cout << "balance" << std::endl;
                deleteFix(toDelete->parent, sideRight);
            }

            delete toDelete;
            return;
        }
        if (toDelete->right == nullptr && toDelete->left != nullptr) {
            if (toDelete == root) {
                root = toDelete->left;
                root->parent = nullptr;
                delete toDelete;
                return;
            }
            if (toDelete == toDelete->parent->right) {
                toDelete->parent->right = toDelete->left;
                toDelete->left->parent = toDelete->parent;
            } else {
                toDelete->parent->left = toDelete->left;
                toDelete->left->parent = toDelete->parent;
            }
//            toDelete->parent->size--;
            toDelete->left->isBlack = toDelete->isBlack;
            delete toDelete;
            return;
        }
        if (toDelete->right != nullptr && toDelete->left == nullptr) {
            if (toDelete == root) {
                root = toDelete->right;
                root->parent = nullptr;
                delete toDelete;
                return;
            }
            if (toDelete == toDelete->parent->right) {
                toDelete->parent->right = toDelete->right;
                toDelete->right->parent = toDelete->parent;
            } else {
                toDelete->parent->left = toDelete->right;
                toDelete->right->parent = toDelete->parent;

            }
//            toDelete->parent->size--;
            toDelete->right->isBlack = toDelete->isBlack;
            delete toDelete;
            return;
        } else {
            Node *successor = toDelete;
            successor = successor->left;

            while (true) {
                if (successor->right != nullptr) {
                    successor->size--;
                    successor = successor->right;
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
            brother = toFix->left;
        else
            brother = toFix->right;
        Node *leftGrandson = brother->left;
        Node *rightGrandson = brother->right;

        if (leftGrandson == nullptr)
            leftGrandson = new Node();
        if (rightGrandson == nullptr)
            rightGrandson = new Node();

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
            //if(leftGrandson->isBlack
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

            if (leftGreatGrandson == nullptr)
                leftGreatGrandson = new Node();
            if (rightGreatGrandson == nullptr)
                rightGreatGrandson = new Node();


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

            if (sideRight && !rightGrandson->isBlack) {
//                std::cout << "fixCase5\n";

                rightGrandson->isBlack = true;
                leftRotate(brother);
                rightRotate(toFix);

            } else if (!sideRight && !leftGrandson->isBlack) {

                std::cout << "fixCase5\n";

                leftGrandson->isBlack = true;
                rightRotate(brother);
                leftRotate(toFix);

            } else {
                std::cout << "fixCase6\n";
                brother->isBlack = false;
                if (toFix->parent != nullptr) {

                    if (toFix == toFix->parent->right)
                        sideRight = true;
                    else
                        sideRight = false;

                    deleteFix(toFix->parent, sideRight);

                }

            }

        }
    }

    Node *get(Node *node, const T &t) {

        if (node == nullptr)
            return nullptr;

        if (t == node->value)
            return node;

        if (t < node->value)
            return get(node->left, t);
        else
            return get(node->right, t);

    }

    void print(Node *node, int level, bool left) const {

        if (node == nullptr)
            return;


        if (node == this->root) {
            std::cout << node->value << " size = " << node->size;
            if (node->isBlack)
                std::cout << " Black\n";
            else
                std::cout << " Red\n";
        } else {
            for (int i = 0; i < level; i++) {

                std::cout << "|\t";

            }
            std::cout << node->value << " size = " << node->size << " ";

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

        print(node->left, level + 1, true);

        print(node->right, level + 1, false);

    }

    Node *getStat(Node *node, int index) {

        int curPos = getSize(node->left) + 1;
        if (curPos == index)
            return node;
        if (curPos > index)
            return getStat(node->left, index);
        else
            return getStat(node->right, index - curPos);

    }

public:

    Tree() {

        this->root = nullptr;
//        size = 0;

    }

    ~Tree() = default;

    void insert(T &t) {

        Node *temp = root;
        Node *futureParent = nullptr;
        Node *toInsert = new Node(t);

        while (temp != nullptr) {

            futureParent = temp;
            temp->size++;

            if (toInsert->value < temp->value)
                temp = temp->left;
            else
                temp = temp->right;

        }

        toInsert->parent = futureParent;

        if (futureParent == nullptr)
            this->root = toInsert;
        else if (toInsert->value < futureParent->value)
            futureParent->left = toInsert;
        else
            futureParent->right = toInsert;

        insertCase1(toInsert);
    }

    void erase(const T &t) {

        erase(root, t);

    }

    T get(const T &t) {

        Node *res = get(root, t);

        if (res == nullptr)
            return T();

        return res->value;

    }

    T getStat(int index) {

        Node *res = getStat(root, index);

        return res->value;

    }

    void print() const {

        print(this->root, 0, true);

    }

};


#endif //LAB2_ORDERSTATTREE__TREE_H
