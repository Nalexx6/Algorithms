//
// Created by Win10Pro on 4/4/2021.
//

#ifndef LAB6_B_TREE__BPLUSTREE_H
#define LAB6_B_TREE__BPLUSTREE_H

#include <iostream>
#include <vector>

template <typename T, typename K>
class BplusTree{

private:

    class Element{
    public:
        K key;
        T value;
        Element(K key, T value){
            this->key = key;
            this->value = value;
        }
    };
    class Node{
    public:
        bool isLeaf{};
        std::vector<Element> elements;
        std::vector<Node*> child;
        Node* parent;
        Node* leftBrother;
        Node* rightBrother;

        Node(bool isLeaf, const std::vector<Element>& elements, const std::vector<Node*>& child){
            this->isLeaf = isLeaf;
            this->elements = elements;
            this->child = child;
            parent = leftBrother = rightBrother = nullptr;
        }

    };

    Node* findLeaf(Node* node, K toFind){
        if(node->isLeaf){
            return node;
        }

        for(int i = 0; i < node->elements.size(); i++){
            if(toFind <= node->elements[i].key){
                return findLeaf(node->child[i], toFind);
            }
        }

        return findLeaf(node->child[node->child.size() - 1], toFind);
    }

    void splitNode(Node* toSplit){

        std::vector<Element> elementsSplit;
        std::vector<Node*> childSplit;

        Element midEl = toSplit->elements[power];
        for(int i = 0; i < power - 1; i++){
            elementsSplit.template emplace_back(toSplit->elements[i + power + 1]);
            childSplit.template emplace_back(toSplit->child[i + power + 1]);
        }
        childSplit.template emplace_back(toSplit->child[power * 2]);

        if(toSplit->isLeaf){
            elementsSplit.template emplace(elementsSplit.begin(), midEl);
        }

        Node* afterSplit = new Node(toSplit->isLeaf, elementsSplit, childSplit);
        for(int i = 0; i < power; i++){
            toSplit->elements.pop_back();
            toSplit->child.pop_back();
        }

        afterSplit->rightBrother = toSplit->rightBrother;
        if(afterSplit->rightBrother != nullptr){
            afterSplit->rightBrother->leftBrother = afterSplit;
        }
        toSplit->rightBrother = afterSplit;
        afterSplit->leftBrother = toSplit;

        if(toSplit == this->root){
            this->root = new Node(false, {midEl}, {toSplit, afterSplit});
            toSplit->parent = root;
            afterSplit->parent = root;
        } else{
            Node* parent = toSplit->parent;
            afterSplit->parent = parent;

            int pos = 0;
            while(pos < parent->elements.size() && parent->elements[pos].key < midEl.key){
                pos++;
            }

            auto it1 = parent->elements.begin() + pos;
            parent->elements.template emplace(it1, midEl);
            auto it2 = parent->child.begin() + pos + 1;
            parent->child.template emplace(it2, afterSplit);

            if(parent->elements.size() == 2 * power){
                splitNode(parent);
            }
        }


    }



    void print(Node *node, int level) const {

        if (node == nullptr)
            return;


        if (node == this->root) {
            for(auto e: node->elements) {
                std::cout << e.key << " ";
            }
            std::cout << "\n";

        } else {
            for (int i = 0; i < level; i++) {

                std::cout << "|\t";

            }
            for(auto e: node->elements) {
                std::cout << e.key << " ";
            }

            std::cout << "parent " << node->parent->elements[0].key << "\n";
        }

        for(auto child: node->child){
            print(child, level + 1);
        }

    }



    int power;
    Node* root;

public:

    BplusTree(int power){
        root = nullptr;
        this->power = power;
    }

    void insert(K key, T value){

        auto* element = new Element(key, value);
        if(root == nullptr){
            std::vector<Element> vector = {*element};
            root = new Node(true, vector, {nullptr, nullptr});
            return;
        }

        Node* toInsert = findLeaf(root, key);
        int pos = 0;
        while (pos < toInsert->elements.size() && toInsert->elements[pos].key < key){
            pos++;
        }

        auto it = toInsert->elements.begin() + pos;
        toInsert->elements.template emplace(it,  *element);
        toInsert->child.template emplace_back(nullptr);

        if(toInsert->elements.size() == power * 2){
            splitNode(toInsert);
        }

    }

    void print(){

        print(root, 0);

    }


};



#endif //LAB6_B_TREE__BPLUSTREE_H
