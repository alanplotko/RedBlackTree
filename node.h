#ifndef NODE_H_
#define NODE_H_

enum type {RED, BLACK};

template <typename T>
struct node
{
    node<T> *right;
    node<T> *left;
    node<T> *parent;
    type color;
    int height;
    std::pair<int, T> data;
    node():right(nullptr),left(nullptr),parent(nullptr),height(1),data(nullptr),color(RED){}
    node(std::pair<int, T> item):right(nullptr),left(nullptr),parent(nullptr),height(1),data(item),color(RED){}
};

#endif
