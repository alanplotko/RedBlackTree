#include "rbt.h"
#include <queue>
#include <vector>
#include <algorithm>

/*-------------------------
    RBT tree destructor
---------------------------*/

template <class T>
rbt<T>::~rbt()
{
    cleanRbt(root);
}

/*----------------------------------
   Destroy all nodes in RBT tree
------------------------------------*/

template <class T>
void rbt<T>::cleanRbt() {
    cleanRbt(root);
    size = 0;
    items.clear();
    root = nullptr;
}

template <class T>
void rbt<T>::cleanRbt(node<T> *nd)
{
    // Stop check if node is nullptr
    if(nd == nullptr) return;

    // If there's a left node, destroy it via a recursive call
    if(nd->left != nullptr) cleanRbt(nd->left);

    // If there's a right node, destroy it via a recursive call
    if(nd->right != nullptr) cleanRbt(nd->right);

    // Delete the node
    delete nd;
}

/*-------------------------------
    Insert pair into RBT tree
---------------------------------*/

template <class T>
void rbt<T>::insert(std::pair<int, T> item)
{
    // Case 1: empty tree, item becomes root
    if(root == nullptr)
    {
        node<T> *nd = new node<T>(item);
        root = nd;
        root->color = BLACK;
    }
    // Case 2: insert into correct position
    else
    {
        node<T>* nd = insert(root, item);

        // Recolor tree based on new node's properties
        insertRecolor(nd);
    }

    // Keep track of tree size
    this->size++;

    // Keep track of items for sorting
    this->items.push_back(item);
}

/*-------------------------------
    Recursive call for insert
---------------------------------*/

template <class T>
node<T>* rbt<T>::insert(node<T> *nd, std::pair<int, T> item)
{
    node<T> *newNode;

    // Case 1: item weight >= current node weight
    if(item.first >= nd->data.first)
    {
        // Case 1a: found open space for insert
        if(nd->right == nullptr)
        {
            newNode = new node<T>(item);
            nd->right = newNode;
            newNode->parent = nd;
        }
        // Case 1b: current space contains node;
        //          keep moving to the right
        else
        {
            insert(nd->right, item);
        }
    }
    // Case 2: item weight < current node weight
    else
    {
        // Case 2a: found open space for insert
        if(nd->left == nullptr)
        {
            newNode = new node<T>(item);
            nd->left = newNode;
            newNode->parent = nd;
        }
        // Case 2b: current space contains node;
        //          keep moving to the left
        else
        {
            insert(nd->left, item);
        }
    }
    return newNode;
}

/*---------------------------------------
    Examine the newly inserted node's
    properties and recolor the tree
-----------------------------------------*/

template <class T>
void rbt<T>::insertRecolor(node<T> *nd)
{
    while(nd != root && nd->parent->color == RED)
    {
        if(nd->parent->parent == nullptr) return;
        if(nd->parent == nd->parent->parent->left)
        {
            node<T> *uncle = nd->parent->parent->right;
            if(uncle != nullptr && uncle->color == RED)
            {
                nd->parent->color = BLACK;
                uncle->color = BLACK;
                nd->parent->parent->color = RED;
                nd = nd->parent->parent;
            }
            else
            {
                if(nd == nd->parent->right)
                {
                    nd = nd->parent;
                    rotateLeft(nd);
                }
                nd->parent->color = BLACK;
                nd->parent->parent->color = RED;
                rotateRight(nd->parent->parent);
            }
        }
        else {
            node<T> *uncle = nd->parent->parent->left;
            if(uncle != nullptr && uncle->color == RED)
            {
                nd->parent->color = BLACK;
                uncle->color = BLACK;
                nd->parent->parent->color = RED;
                nd = nd->parent->parent;
            }
            else
            {
                if(nd == nd->parent->left)
                {
                    nd = nd->parent;
                    rotateRight(nd);
                }
                nd->parent->color = BLACK;
                nd->parent->parent->color = RED;
                rotateLeft(nd->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

/*--------------------------------------
    Get balance factor for rotations
----------------------------------------*/

template <class T>
int rbt<T>::balanceFactor(node<T> *nd)
{
    int left = (nd->left == nullptr ? 0 : nd->left->height);
    int right = (nd->right == nullptr ? 0 : nd->right->height);
    return right - left;
}

/*---------------------------------------
    Set node's height to the larger
    height of its child nodes, plus 1
-----------------------------------------*/

template <class T>
void rbt<T>::maxHeight(node<T> *nd)
{
    int left = (nd->left == nullptr ? 0 : nd->left->height);
    int right = (nd->right == nullptr ? 0 : nd->right->height);
    nd->height = std::max(left, right) + 1;
}

/*-----------------------------------
    Left rotation with pivot node
-------------------------------------*/

template <class T>
void rbt<T>::rotateLeft(node<T> *nd)
{
    node<T> *tmp = nd->right;
    tmp->parent = nd->parent;
    nd->right = tmp->left;

    if (nd->right != nullptr)
    {
        nd->right->parent = nd;
    }

    tmp->left = nd;
    nd->parent = tmp;

    if (tmp->parent != nullptr)
    {
        if (tmp->parent->right == nd)
        {
            tmp->parent->right = tmp;
        }
        else
        {
            tmp->parent->left = tmp;
        }
    }
    else
    {
        root = tmp;
    }

    maxHeight(nd);
    maxHeight(tmp);
    nd = tmp;
}

/*------------------------------------
    Right rotation with pivot node
--------------------------------------*/

template <class T>
void rbt<T>::rotateRight(node<T> *nd)
{
    node<T> *tmp = nd->left;

    tmp->parent = nd->parent;

    nd->left = tmp->right;

    if(nd->left != nullptr)
    {
        nd->left->parent = nd;
    }

    tmp->right = nd;
    nd->parent = tmp;

    if (tmp->parent != nullptr)
    {
        if (tmp->parent->right == nd)
        {
            tmp->parent->right = tmp;
        }
        else
        {
            tmp->parent->left = tmp;
        }
    }
    else
    {
        root = tmp;
    }

    maxHeight(nd);
    maxHeight(tmp);
    nd = tmp;
}

/*-----------------------------------
    Search and return node by key
-------------------------------------*/

template <class T>
node<T>* rbt<T>::search(int key)
{
    if(root == nullptr) return nullptr;
    return search(key, root);
}

/*-------------------------------
    Recursive call for search
---------------------------------*/

template <class T>
node<T>* rbt<T>::search(int key, node<T> *nd)
{
    if(nd == nullptr) return nullptr;
    if(key == nd->data.first) return nd;
    if(key > nd->data.first) return search(key, nd->right);

    return search(key, nd->left);
}

/*-------------------------------------
    Print node values between
    traversing left and right trees
---------------------------------------*/

template <class T>
void rbt<T>::inorder()
{
    if(root == nullptr) return;
    inorder(root);
}

/*---------------------------------
    Recursive call for inorder
-----------------------------------*/

template <class T>
void rbt<T>::inorder(node<T>* nd)
{
    if(nd == nullptr) return;
    inorder(nd->left);
    std::cout << nd->data.first;
    inorder(nd->right);
}

/*--------------------------------------
    Print node values in level order
----------------------------------------*/

template <class T>
void rbt<T>::printBreadthFirst()
{
    if(root == nullptr) return;
    std::queue<node<T>*> nodeSet;
    nodeSet.push(root);
    while(!nodeSet.empty())
    {
        node<T>* front = nodeSet.front();
        if(front->left != nullptr)
        {
            nodeSet.push(front->left);
        }
        if(front->right != nullptr)
        {
            nodeSet.push(front->right);
        }
        node<T> *p = front->parent;
        int test = 0;
        if(p != nullptr)
        {
            test = front->parent->data.first;
        }
        std::cout << front->data.first << ": " << front->color << " (" << test << ")" << std::endl;
        nodeSet.pop();
    }
    std::cout << std::endl;
}

/*--------------------------
    Return size of tree
----------------------------*/

template <class T>
int rbt<T>::getSize() { return this->size; }

/*-------------------
    Get next node
---------------------*/

template <class T>
node<T>* rbt<T>::getNextNode(node<T> *nd)
{
    node<T> *tmp = nd->right;
    if(tmp != nullptr)
    {
        return getSmallestNode(tmp->right);
    }
    else
    {
        tmp = nd->parent;
        while(tmp->right == nd)
        {
            nd = tmp->right;
            tmp = tmp->parent;
        }

        if(tmp == root) return nullptr;
        return tmp;
    }
}

template <class T>
node<T>* rbt<T>::getSmallestNode(node<T> *nd)
{
    node<T> *current = nd;

    while(current->left != nullptr)
    {
        current = current->left;
    }

    return current;
}

template <class T>
node<T>* rbt<T>::getLargestNode(node<T> *nd)
{
    node<T> *current = nd;

    while(current->right != nullptr)
    {
        current = current->right;
    }

    return current;
}

/*-------------------------------------
    Delete node associated with key
---------------------------------------*/

template <class T>
bool rbt<T>::deleteKey(int key)
{
    node<T> *result = search(key);

    if(result == nullptr) return false;

    deleteKey(result);
    for(int i = 0; i < size; i++)
    {
        if(items[i] == result->data)
        {
            items.erase(items.begin() + i);
            break;
        }
    }
    size--;
    return true;
}

template <class T>
void rbt<T>::deleteKey(node<T> *nd)
{
    node<T> *tmp = nd;

    if(tmp == nullptr) return;

    // Node has 2 children
    if(tmp->left != nullptr && tmp->right != nullptr)
    {
        tmp = getLargestNode(tmp->left);
        nd->data = tmp->data;
    }
    
    node<T> *remainingChild;

    if(tmp->left != nullptr)
    {
        remainingChild = tmp->left;
    }
    else
    {
        remainingChild = tmp->right;
    }
    
    if(remainingChild != nullptr)
    {
        if(tmp == root)
        {
            root = remainingChild;
            remainingChild->parent = nullptr;
        }
        else if(tmp == tmp->parent->left)
        {
            tmp->parent->left = remainingChild;
            remainingChild->parent = tmp->parent;
        }
        else
        {
            tmp->parent->right = remainingChild;
            remainingChild->parent = tmp->parent;
        }

        if(getColor(tmp) == BLACK) deleteRecolor(remainingChild);

        delete tmp;
    }
    else if(tmp == root)
    {
        root = nullptr;
    }
    else
    {
        if(getColor(tmp) == BLACK) deleteRecolor(tmp);

        if(tmp->parent != nullptr)
        {
            if(tmp == tmp->parent->right)
            {
                tmp->parent->right = nullptr;
            }
            else
            {
                tmp->parent->left = nullptr;
            }
        }

        delete tmp;
    }
}

template <class T>
type rbt<T>::getColor(node<T> *nd)
{
    if(nd == nullptr) return BLACK;
    return nd->color;
}

template <class T>
void rbt<T>::deleteRecolor(node<T> *nd)
{
    while(nd != root && getColor(nd) == BLACK)
    {
        if(nd == nd->parent->left)
        {
            node<T> *sibling = nd->parent->right;
            
            if(getColor(sibling) == RED)
            {
                sibling->color = BLACK;
                sibling->parent->color = RED;
                rotateLeft(nd->parent);
                sibling = nd->parent->right;
            }
            
            if(getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
            {
                sibling->color = RED;
                nd = nd->parent;
            }
            else
            {
                if(getColor(sibling->right) == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = nd->parent->right;
                }
                sibling->color = nd->parent->color;
                nd->parent->color = BLACK;
                if(sibling->right != nullptr)
                {
                    sibling->right->color = BLACK;
                }
                rotateLeft(nd->parent);
                nd = root;
            }
        }
        else
        {
            node<T> *sibling = nd->parent->left;

            if(getColor(sibling) == RED)
            {
                sibling->color = BLACK;
                nd->parent->color = RED;
                rotateRight(nd->parent);
                sibling = nd->parent->left;
            }
    
            if(getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
            {
                sibling->color = RED;
                nd = nd->parent;
            }
            else
            {
                if(getColor(sibling->left) == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = nd->parent->left;
                }
                sibling->color = nd->parent->color;
                nd->parent->color = BLACK;
                if(sibling->left != nullptr)
                {
                    sibling->left->color = BLACK;
                }
                rotateRight(nd->parent);
                nd = root;
            }
        }
    }
    nd->color = BLACK;
}

/*---------------------------
    Convert sorted vector
    into RBT, vice-versa
-----------------------------*/

template <class T>
rbt<T> rbt<T>::sortedVectorToTree(std::vector<std::pair<int, T> > items)
{
    rbt<T> tree;
    unsigned int size = items.size();
    for(unsigned int i = 0; i < size; i++)
    {
        tree.insert(items[i]);
    }
    return tree;
}

template <class T>
std::vector<std::pair<int, T> > rbt<T>::treeToSortedVector()
{
    // Pairs have their own sorting algorithm implemented
    // by default using their keys for comparisons
    std::sort(this->items.begin(), this->items.end());
    return this->items;
}
