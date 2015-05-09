#ifndef RBT_H_
#define RBT_H_

#include "node.h"
#include <iostream>
#include <utility>
#include <vector>

template <class T>
class rbt
{
    public:
        rbt():root(nullptr),size(0){}
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
        rbt<T> sortedArrayToTree(std::vector<std::pair<int, T> > items);
        std::vector<std::pair<int, T> > treeToSortedArray();
        node<T>* getNextNode(node<T> *nd);
        node<T>* getSmallestNode(node<T> *nd);
        node<T>* getLargestNode(node<T> *nd);
        void deleteKey(int key);
        void insertRecolor(node<T> *nd);
        void deleteRecolor(node<T> *nd);
        type getColor(node<T> *nd);
        int getSize();
    private:
        node<T> *root;
        int size;
        std::vector<std::pair<int, T> > items;
        void insert(node<T> *nd, std::pair<int, T> item);
        void deleteKey(node<T> *nd);
        node<T>* search(int key, node<T> *nd);
        void inorder(node<T> *nd);
        void cleanRbt(node<T> *nd);
        void inOrderColor(node<T> *nd);
};

#include "rbt.cpp"


#endif
