//
// Created by Win10Pro on 4/3/2021.
//

#ifndef LAB7_BINOMIALHEAP__BINOMIALHEAP_H
#define LAB7_BINOMIALHEAP__BINOMIALHEAP_H

#include <iostream>
#include <vector>

template <typename T>
class BinomialHeap{

private:

    class Node{
    public:

        Node* parent;
        Node* brother;
        Node* child;
        int degree;
        T value;

        Node(){

        }

        Node(T& value){
            parent = nullptr;
            brother = nullptr;
            child = nullptr;
            degree = 0;
            this->value = value;
        }
    };

    Node* merge(Node* toMerge1, Node* toMerge2){
        Node* res;
        if(lessEquals(toMerge1, toMerge2)){
            res = toMerge1;
            toMerge1 = toMerge1->brother;
        } else {
            res = toMerge2;
            toMerge2= toMerge2->brother;
        }
        Node* toReturn = res;
        while(toMerge1 != nullptr || toMerge2 != nullptr) {
            if (lessEquals(toMerge1, toMerge2)) {
                res->brother = toMerge1;
                res = toMerge1;
                toMerge1 = toMerge1->brother;
            } else {
                res->brother = toMerge2;
                res = toMerge2;
                toMerge2 = toMerge2->brother;
            }
        }

        return toReturn;
    }

    bool lessEquals(Node* a, Node* b){
        if(a == nullptr){
            return false;
        }
        if(b == nullptr)
            return true;
        if(a->degree <= b->degree)
            return true;

        return false;
    }

    Node* heapUnion(Node* toUnite1, Node* toUnite2){

        Node* unitedHead = merge(toUnite1,  toUnite2);

//        testPrint(unitedHead);

        Node* prev = nullptr;
        Node* temp = unitedHead;
        Node* next = unitedHead->brother;
        while(next != nullptr){
            std::cout<<next->value<<"\n";
            if(temp->degree != next->degree){
                prev = temp;
                temp = next;
            } else if(next->brother != nullptr && next->degree == next->brother->degree){
                    prev = temp;
                    temp = next;
            } else if(temp->value <= next->value){
                temp->brother = next->brother;
                link(next, temp);
            } else {
                if(prev == nullptr){
                    unitedHead = next;
                } else {
                    prev->brother = next;
                }
                link(temp, next);
                temp = next;
            }

            next = temp->brother;
        }

        return unitedHead;

    }

    void testPrint(Node* node){
        while (node!= nullptr){
            std::cout << node->value << "\t";
            node = node->brother;
        }
        std::cout << "\n";;
    }

    void link(Node* greaterRoot, Node* lesserRoot){

        greaterRoot->parent = lesserRoot;
        greaterRoot->brother = lesserRoot->child;
        lesserRoot->child = greaterRoot;
        lesserRoot->degree++;

    }

    void print(Node* node, int degree){

        if(node == nullptr) {
            return;
        }

        for(int i = 0; i < degree; i++){
            std::cout << "\t";
        }
        std::cout<< node->value;
        if(node->parent != nullptr){
            std::cout << "\tparent\t" << node->parent->value;
        }
        std::cout << "\n";

        print(node->child, degree + 1);
        print(node->brother, degree);

    }

    Node* head;

public:

    BinomialHeap(){
        head = nullptr;
    }

    void insert(T& t){

        Node* toInsert = new Node(t);
        this->head = heapUnion(toInsert, head);
    }

    void print(){
//        Node* temp = head;
//        while (temp != nullptr){
//
//            print(temp, temp->degree);
//        }
        print(head, 0);
    }


};

#endif //LAB7_BINOMIALHEAP__BINOMIALHEAP_H
