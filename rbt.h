#ifndef RBT_H_
#define RBT_H_

#include "node.h"
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

template <class T>
class rbt
{
    public:

        rbt():root(nullptr),size(0){}
        ~rbt();

        // Tree rotations
        void rotateLeft(node<T> *nd);
        void rotateRight(node<T> *nd);

        // Tree restructuring
        void maxHeight(node<T> *nd);

        // Tree recoloring
        void insertRecolor(node<T> *nd);
        void deleteRecolor(node<T> *nd);

        // Tree data manipulations
        void insert(std::pair<int, T> item);
        node<T>* search(int key);
        bool deleteKey(int key);

        // Tree conversions: to/from a sorted vector
        void sortedVectorToTree(std::vector<std::pair<int, T> > items);
        std::vector<std::pair<int, T> > treeToSortedVector();

        // Tree traversal
        void inorder();
        void printBreadthFirst();

        // Tree helper functions
        node<T>* getNextNode(node<T> *nd);
        node<T>* getSmallestNode(node<T> *nd);
        node<T>* getLargestNode(node<T> *nd);
        type getColor(node<T> *nd);
        int getSize();
        std::queue<node<T>*> getNodeBreadthFirst();

        // Clear the tree
        void cleanRbt();

    private:

        // Tree variables
        node<T> *root;
        int size;
        std::vector<std::pair<int, T> > items;

        // Tree data manipulation functions
        void insert(node<T> *nd, std::pair<int, T> item);
        node<T>* search(int key, node<T> *nd);
        void deleteKey(node<T> *nd);

        // Tree traversal
        void inorder(node<T> *nd);

        // Tree destructor helper
        void cleanRbt(node<T> *nd);
};

#include "rbt.cpp"


#endif
