#ifndef RBT_H_
#define RBT_H_

#include "node.h"
#include <iostream>
#include <utility>

template <class T>
class rbt
{
    public:
        rbt():root(nullptr){}
        ~rbt();
        void insert(std::pair<int, T> item);
        //friend std::ostream& operator<<(std::ostream &out, rbt &willow);
        int balanceFactor(node<T> *nd);
        void maxHeight(node<T> *nd);
        void rotateLeft(node<T> *nd);
        void rotateRight(node<T> *nd);
        node* search(int key);
        void inorder();
        void printBreadthFirst();
        rbt* sortedArray(std::pair<int, T>[]);
        void deleteKey(int key);
    private:
        node<T> *root;
        void insert(node<T> *nd, std::pair<int, T> item);
        node<T>* search(node<T> *nd, int key);
        void inorder(node<T> *nd);
        void cleanRbt(node<T> *nd);
};

#include "rbt.cpp"


#endif
