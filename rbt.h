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
        node<T>* search(int key);
        void inorder();
        void printBreadthFirst();
        rbt* sortedArray(std::pair<int, T> items[]);
        void deleteKey(int key);
        void inOrderColor();
        
        void pathCheck(node<T> *nd);
        
        //Color helper functions
        void childCheck(node<T> *nd);
        void leftLeft(node<T> *curNd, node<T> *grandPa, node<T> *dad);
        void leftRight(node<T> *curNd, node<T> *grandPa, node<T> *dad);
        void rightRight(node<T> *curNd, node<T> *grandPa, node<T> *dad);
        void rightLeft(node<T> *curNd, node<T> *grandPa, node<T> *dad);
    private:
        node<T> *root;
        void insert(node<T> *nd, std::pair<int, T> item);
        node<T>* search(int key, node<T> *nd);
        void inorder(node<T> *nd);
        void cleanRbt(node<T> *nd);
        void inOrderColor(node<T> *nd);
};

#include "rbt.cpp"


#endif
