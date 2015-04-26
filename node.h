#ifndef NODE_H_
#define NODE_H_

enum type{RED, BLACK};

struct node
{
    node *right;
    node *left;
    node *parent;
    type color; 
    int height;
    double data;
    node():right(nullptr),left(nullptr),parent(nullptr),height(1),data(0),color(RED){}
    node(double dta):right(nullptr),left(nullptr),parent(nullptr),height(1),data(dta),color(RED){}
};

#endif
