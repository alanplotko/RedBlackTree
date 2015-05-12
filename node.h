#ifndef NODE_H_
#define NODE_H_

#include <utility>

enum type {RED, BLACK};

template <typename T>
struct node
{
    node<T> *left;
    node<T> *right;
    node<T> *parent;
    type color;
    int height;
    int width;
    std::pair<int, T> data;

    /*  RBT nodes are red by default, but may change in color
        at any time when the tree undergoes recoloring */
    
    node():left(nullptr),right(nullptr),parent(nullptr),color(RED),height(1),width(0),data(nullptr){}
    node(std::pair<int, T> item):left(nullptr),right(nullptr),parent(nullptr),color(RED),height(1),data(item){}
};

#endif
