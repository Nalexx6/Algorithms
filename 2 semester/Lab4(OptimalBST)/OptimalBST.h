//
// Created by Win10Pro on 3/3/2021.
//

#ifndef LAB4_OPTIMALBST__OPTIMALBST_H
#define LAB4_OPTIMALBST__OPTIMALBST_H

#include <iostream>
#include <vector>
#include <cfloat>

template <typename T>
class OptimalBST{

private:
    class Node{

    public:
        T value;
        Node* parent;
        Node* left;
        Node* right;
        double probability{};


        Node() {
            left = right = parent = nullptr;
            probability = 0;
        }
        Node(const T& value, double probability){
            this->value = value;
            left = right = parent = nullptr;
            this->probability = probability;
        }

        ~Node() = default;
    };

    //tree body
    Node* root;

    //input data
    std::vector<T> elements;
    std::vector<double> probs;
    std::vector<double> fictProbs;

    //generated tables
    std::vector<std::vector<double>> expectedValues;
    std::vector<std::vector<double>> probsSum;
    std::vector<std::vector<int>> roots;


    void generateTables(){

        int size = elements.size();
        for(int i = 1; i < size + 2; i++){
            expectedValues[i][i - 1] = fictProbs[i - 1];
            probsSum[i][i - 1] = fictProbs[i - 1];
        }
        int j;
        double t;
        for(int l = 1; l < size + 1; l++){

            for(int i = 1; i < size - l + 2; i++){

                j = i + l - 1;

                expectedValues[i][j] = DBL_MAX;
                probsSum[i][j] = probsSum[i][j - 1] + probs[j - 1] + fictProbs[j];

                for(int r = i; r < j + 1; r++){

                    t = expectedValues[i][r - 1] + expectedValues[r + 1][j] + probsSum[i][j];
                    std::cout<<t<<"\t";
                    if(t < expectedValues[i][j]){

                        expectedValues[i][j] = t;
                        roots[i][j] = r;

                    }

                }

            }

        }
        std::cout <<std::endl;

    }

    Node* constructBST( Node* node, int lo, int hi){

        if(lo > hi)
            return new Node(T(), fictProbs[hi]);

        int currentIndex = roots[lo][hi] - 1;
        Node* tempRoot = new Node(elements[currentIndex], probs[currentIndex]);

        tempRoot->left = constructBST(tempRoot, lo, roots[lo][hi] - 1);
        tempRoot->right = constructBST(tempRoot, roots[lo][hi] + 1, hi);

        tempRoot->parent = node;
        return tempRoot;

    }

    void print(Node* node, int level, bool left) const{

        if(node == nullptr)
            return;


        if(node == this->root) {
            std::cout << node->value << std::endl;
            std::cout << " probability " <<  node->probability << "\n";
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
            std::cout << " probability " <<  node->probability << "\n";
        }

        print(node->left, level + 1, true);

        print(node->right, level + 1, false);

    }

    void destroy(Node* toDestroy){
        if(toDestroy == nullptr)
            return;

        destroy(toDestroy->left);
        destroy(toDestroy->right);

        delete toDestroy;

    }
public:

    OptimalBST( const std::vector<T>& elements, const std::vector<double>& probs,
                const std::vector<double>& fictProbs){


        this->root = nullptr;
        this->elements = elements;
        this->probs = probs;
        this->fictProbs = fictProbs;

        int size = elements.size();
        this->expectedValues.assign(size + 2, {});
        this->probsSum.assign(size + 2, {});
        this->roots.assign(size + 1, {});

        for(int i = 0; i < size + 2; i++){

            expectedValues[i].assign(size + 1, 0);
            probsSum[i].assign(size + 1, 0);


        }
        for(int i = 0; i < size + 1; i++){

            roots[i].assign(size + 1, 0);
        }

//        for(int i = 0; i < size + 1; i++){
//
//            roots[i][i] = i;
//
//        }




        generateTables();

        std::cout << "----------------------expected values--------------\n";
        for(auto&  i : expectedValues) {
            for (auto& j : i) {

                std::cout << j << "\t";

            }
            std::cout <<"\n";
        }
        std::cout << "----------------------probs sum--------------\n";
        for(auto&  i : probsSum) {
            for (auto& j : i) {

                std::cout << j << "\t";

            }
            std::cout <<"\n";
        }
        std::cout << "----------------------roots--------------\n";
        for(auto&  i : roots) {
            for (auto& j : i) {

                std::cout << j << "\t";

            }
            std::cout <<"\n";
        }


        this->root = constructBST(nullptr, 1, size);

    }

    ~OptimalBST(){

        for(int i = 0; i < elements.size() + 2; i++){

            expectedValues[i].clear();
            probsSum[i].clear();

        }
        for(int i = 0; i < elements.size() + 1; i++){

            roots[i].clear();
        }

        expectedValues.clear();
        probsSum.clear();
        roots.clear();

        destroy(this->root);
        std::cout<< "tree destroyed\n";

    }

    void print(){

        print(this->root, 0, true);

    }



};

#endif //LAB4_OPTIMALBST__OPTIMALBST_H
