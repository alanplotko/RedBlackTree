#ifndef NODE_H_
#define NODE_H_

struct node
{
    node *right;
    node *left;
    node *parent;
    int height;
    double data;
    node():right(nullptr),left(nullptr),parent(nullptr),height(1),data(0){}
    node(double dta):right(nullptr),left(nullptr),parent(nullptr),height(1),data(dta){}
};

#endif
