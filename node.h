#ifndef NODE_H_
#define NODE_H_

#include <utility>

enum type {RED, BLACK};

template <typename T>
struct node
{
    node<T> *left, *right, *parent;
    type color;
    int height;
    std::pair<int, T> data;

    /*  RBT nodes are red by default, but may change in color
        at any time when the tree undergoes recoloring */
    
    node():right(nullptr),left(nullptr),parent(nullptr),height(1),data(nullptr),color(RED){}
    node(std::pair<int, T> item):right(nullptr),left(nullptr),parent(nullptr),height(1),data(item),color(RED){}
};

#endif
