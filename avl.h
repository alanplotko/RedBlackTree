#ifndef AVL_H_
#define AVL_H_

#include <iostream>
#include "node.h"

class avl
{
    public:
        avl():root(nullptr){}
        ~avl();
        void insert(double dta);
        friend std::ostream& operator<<(std::ostream &out, avl &willow);
        int balanceFactor(node *nd);
        void maxHeight(node *nd);
        void rotateLeft(node *nd);
        void rotateRight(node *nd);
        node* find(double dta);
        void inorder();
        void printBreadthFirst();
    
    private:
        node* root;
        void insert(node* nd, double dta);
        node* find(node* nd, double dta);
        void inorder(node* nd);
        void cleanAvl(node* nd);
};


#endif
