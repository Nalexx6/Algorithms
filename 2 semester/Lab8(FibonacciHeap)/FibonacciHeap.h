//
// Created by Win10Pro on 4/5/2021.
//

#ifndef LAB8_FIBONACCIHEAP__FIBONACCIHEAP_H
#define LAB8_FIBONACCIHEAP__FIBONACCIHEAP_H

#include <iostream>
#include <vector>
#include <set>

template <typename T>
class FibonacciHeap{

private:
    class Node{
    public:
        T value;
        Node* child;
        Node* parent;
        Node* leftBrother;
        Node* rightBrother;
        int degree;
        bool mark;

        //auxiliary field for extract min;
        bool visited;

        explicit Node(T value){
            this->value = value;
            child = parent = nullptr;
            leftBrother = rightBrother = this;
            this->degree = 0;
            mark = false;
            visited = false;
        }

    };

    void addToRootsList(Node* toAdd){
        Node* leftHeadBrother = head->leftBrother;
        toAdd->leftBrother->rightBrother = head;
        head->leftBrother = toAdd->leftBrother;
        toAdd->leftBrother = leftHeadBrother;
        leftHeadBrother->rightBrother = toAdd;

        if(head->value > toAdd->value) {
            head = toAdd;
        }
    }

    void eraseFromRootsList(Node* toDelete){

        toDelete->leftBrother->rightBrother = toDelete->rightBrother;
        toDelete->rightBrother->leftBrother = toDelete->leftBrother;

        if(toDelete == head){
            head = toDelete->leftBrother;
        }
    }

    Node* heapUnion(Node* toUnite1, Node* toUnite2){

        if(toUnite1 == nullptr){
            return  toUnite2;
        }
        if(toUnite2 == nullptr){
            return  toUnite1;
        }

        toUnite1->rightBrother->leftBrother = toUnite2->leftBrother;
        toUnite2->leftBrother->rightBrother = toUnite1->rightBrother;
        toUnite1->rightBrother = toUnite2;
        toUnite2->leftBrother = toUnite1;

        if(toUnite1->value > toUnite2->value){
            return toUnite2;
        }

        return toUnite1;
    }

    void consolidate(){
        std::vector<Node*> degrees;
        degrees.resize(size, nullptr);

        Node* temp = head;
        Node* toLink;
        int d;
        while(!temp->visited && temp->leftBrother != temp){
            d = temp->degree;
            temp->visited = true;
            while (degrees[d] != nullptr){
                toLink = degrees[d];
                if(temp->value <= toLink->value){
                    link(toLink, temp);
                } else{
                    link(temp, toLink);
                    temp = toLink;
                }
                degrees[d] = nullptr;
                d++;
            }
            degrees[d] = temp;
            temp = temp->rightBrother;
        }

        temp = head;

        do {
            if(temp->value < head->value){
                head = temp;
            }
            temp = temp->rightBrother;
        } while (temp != head);

    }

    void link(Node* greaterRoot, Node* lesserRoot){
        eraseFromRootsList(greaterRoot);

        if(lesserRoot->child != nullptr) {
            greaterRoot->leftBrother = lesserRoot->child->leftBrother;
            greaterRoot->rightBrother = lesserRoot->child;

            greaterRoot->leftBrother->rightBrother = greaterRoot;
            greaterRoot->rightBrother->leftBrother = greaterRoot;
        } else{
            greaterRoot->leftBrother = greaterRoot;
            greaterRoot->rightBrother = greaterRoot;
        }

        lesserRoot->child = greaterRoot;
        greaterRoot->parent = lesserRoot;
        lesserRoot->degree++;
        greaterRoot->mark = false;

        if(greaterRoot == head){
            head = lesserRoot;
        }
    }

    void print(Node* node, int degree){

        if(node == nullptr) {
            return;
        }

        for(int i = 0; i < degree; i++){
            std::cout << "\t";
        }
        if(node == head){
            std::cout << "head ";
        }
        std::cout<< node->value << " | leftBrother " << node->leftBrother->value
                                << " | rightBrother " << node->rightBrother->value
                                << " | degree " << node->degree;
        if(node->parent != nullptr){
            std::cout << "\tparent\t" << node->parent->value;
        }
        std::cout << "\n";

        print(node->child, degree + 1);
        if((node->parent && node->leftBrother != node->parent->child) ||
                (!node->parent && node->leftBrother != head)) {
            print(node->leftBrother, degree);
        }

    }

    Node* head;
    int size{};

public:

    FibonacciHeap(){
        this->head = nullptr;
        this->size = 0;
    }

    void insert(T t){

        Node* toInsert = new Node(t);

        if(head == nullptr){
            head = toInsert;
        } else {
            addToRootsList(toInsert);
        }

        size++;

    }

    T min(){
        return head->value;
    }

    T extractMin(){

        Node* toDelete = head;

        Node* temp = toDelete->child;

        if(temp != nullptr) {
            addToRootsList(temp);
            temp = head;
            do {
                temp->parent = nullptr;
                temp->visited = false;
                temp = temp->rightBrother;
            } while (temp != head);

        }


        eraseFromRootsList(toDelete);
        if(toDelete == toDelete->rightBrother){
            head = nullptr;
        } else{
            consolidate();
        }

        size--;
        return toDelete->value;
    }

    void print(){
        print(head, 0);
    }

};

#endif //LAB8_FIBONACCIHEAP__FIBONACCIHEAP_H
