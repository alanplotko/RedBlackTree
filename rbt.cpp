#include "rbt.h"
#include <queue>
#include <vector>
#include <algorithm>

/*-----------------------------------
    RBT tree destructor starting
    at the root node
-------------------------------------*/

template <class T>
rbt<T>::~rbt() { cleanRbt(root); }

/*-----------------------------------
    Called by the destructor;
    destroys all nodes in RBT tree
-------------------------------------*/

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

/*-----------------------------------
    Insert std::pair into RBT tree
-------------------------------------*/

template <class T>
void rbt<T>::insert(std::pair<int, T> item)
{
    if(root == nullptr)
    {
        node<T> *nd = new node<T>(item);
        root = nd;
        root->color = BLACK;
        // DEBUG: // std::cout << nd->data.first << ", Height: " << nd->height << ", Bfactor: " << this->balanceFactor(nd) << std::endl;
    }
    else
    {
        insert(root, item);
    }
    this->size++;
    this->items.push_back(item);
}

/*-----------------------------------
    Recursive call for insert
-------------------------------------*/

template <class T>
void rbt<T>::insert(node<T> *nd, std::pair<int, T> item)
{
    node<T>* newNode;
    if(item.first > nd->data.first)
    {
        if(nd->right == nullptr)
        {
            newNode = new node<T>(item);
            nd->right = newNode;
            newNode->parent = nd;
        }
        else
        {
            insert(nd->right, item);
        }
    }
    else
    {
        if(nd->left == nullptr)
        {
            newNode = new node<T>(item);
            nd->left = newNode;
            newNode->parent = nd;
        }
        else
        {
            insert(nd->left, item);
        }
    }

    insertRecolor(newNode);

    //inOrderColor();
    
    // Recalculate heights
    /*maxHeight(nd);

    int bfactor = this->balanceFactor(nd);

    // DEBUG: // std::cout << nd->data << ", Height: " << nd->height << ", Bfactor: " << bfactor << std::endl;

    if(bfactor == -2)
    {
        if(this->balanceFactor(nd->left) == -1)
        {
            // DEBUG: // std::cout << "Rotating right" << std::endl;
            this->rotateRight(nd);
        }
        else
        {
            // DEBUG: // std::cout << "Rotating left, right" << std::endl;
            this->rotateLeft(nd->left);
            this->rotateRight(nd);
        }
    }
    else if(bfactor == 2)
    {
        if(this->balanceFactor(nd->right) == 1)
        {
            // DEBUG: // std::cout << "Rotating left" << std::endl;
            this->rotateLeft(nd);
        }
        else
        {
            // DEBUG: // std::cout << "Rotating right, left" << std::endl;
            this->rotateRight(nd->right);
            this->rotateLeft(nd);
        }
    }*/
}

template <class T>
void rbt<T>::insertRecolor(node<T> *nd)
{
    while(nd != root && nd->parent->color == RED)
    {
        // DEBUG: // std::clog << "Attempting to insert recolor " << nd->data.first << std::endl;
        if(nd->parent->parent == nullptr) return;
        if(nd->parent == nd->parent->parent->left)
        {
            // DEBUG: // std::clog << nd->data.first << " is on left" << std::endl;
            node<T> *uncle = nd->parent->parent->right;
            // DEBUG: // std::clog << "Uncle: " << uncle->data.first;
            if(uncle != nullptr && uncle->color == RED)
            {
                // DEBUG: // std::clog << ", color: red" << std::endl;
                nd->parent->color = BLACK;
                uncle->color = BLACK;
                nd->parent->parent->color = RED;
                // DEBUG: // std::clog << "Grandpa: " << nd->parent->parent->data.first << std::endl;
                nd = nd->parent->parent;
            }
            else
            {
                // DEBUG: // std::clog << ", color: black" << std::endl;
                if(nd == nd->parent->right)
                {
                    nd = nd->parent;
                    rotateLeft(nd);
                }
                nd->parent->color = BLACK;
                // DEBUG: // std::clog << "Grandpa: " << nd->parent->parent->data.first << std::endl;
                nd->parent->parent->color = RED;
                rotateRight(nd->parent->parent);
            }
        }
        else {
            // DEBUG: // std::clog << nd->data.first << " is on right" << std::endl;
            node<T> *uncle = nd->parent->parent->left;
            // DEBUG: // std::clog << "Uncle: " << uncle->data.first << std::endl;
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

/*-----------------------------------
    Get balance factor for rotations
-------------------------------------*/

template <class T>
int rbt<T>::balanceFactor(node<T> *nd)
{
    int left = (nd->left == nullptr ? 0 : nd->left->height);
    int right = (nd->right == nullptr ? 0 : nd->right->height);
    return right - left;
}

/*-----------------------------------
    Set node's height to the larger
    height of its child nodes, plus 1
-------------------------------------*/

template <class T>
void rbt<T>::maxHeight(node<T> *nd)
{
    int left = (nd->left == nullptr ? 0 : nd->left->height);
    int right = (nd->right == nullptr ? 0 : nd->right->height);
    nd->height = std::max(left, right) + 1;
}

/*-----------------------------------
    Rotate RBT tree to the left
-------------------------------------*/

template <class T>
void rbt<T>::rotateLeft(node<T> *nd)
{
    // DEBUG: // std::cout << "Working left with " << nd->data.first << std::endl;
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

/*-----------------------------------
    Rotate RBT tree to the right
-------------------------------------*/

template <class T>
void rbt<T>::rotateRight(node<T> *nd)
{
    // DEBUG: // std::cout << "Working right with " << nd->data.first << std::endl;

    node<T> *tmp = nd->left;

    // DEBUG: // std::cout << "Set tmp to " << nd->left->data.first << std::endl;

    tmp->parent = nd->parent;

    // DEBUG: // T test = (nd->parent == nullptr ? 0 : nd->parent->data.first);
    // DEBUG: // std::cout << "Set tmp->parent to " << test << std::endl;

    nd->left = tmp->right;

    // DEBUG: // std::cout << "Set nd->left to " << tmp->right << std::endl;

    if(nd->left != nullptr)
    {
    // DEBUG: // std::cout << "Set nd->left->parent to " << nd->data.first << std::endl;
    nd->left->parent = nd;
    }

    tmp->right = nd;

    // DEBUG: // std::cout << "Set tmp->right to " << nd->data.first << std::endl;

    nd->parent = tmp;

    // DEBUG: // std::cout << "Set nd->parent to " << tmp->data.first << std::endl;

    // DEBUG: // T test2 = (tmp->parent == nullptr ? 0 : tmp->parent->data.first);
    // DEBUG: // std::cout << "tmp->parent is " << test2 << std::endl;

    if (tmp->parent != nullptr)
    {
        if (tmp->parent->right == nd)
        {
            tmp->parent->right = tmp;
            // DEBUG: // std::cout << "Set tmp->parent->right to " << tmp->data.first << std::endl;
        }
        else
        {
            tmp->parent->left = tmp;
            // DEBUG: // std::cout << "Set tmp->parent->left to " << tmp->data.first << std::endl;
        }
    }
    else
    {
        root = tmp;
    }

    maxHeight(nd);

    // DEBUG: // std::cout << "Set nd->height to " << nd->height << std::endl;

    maxHeight(tmp);

    // DEBUG: // std::cout << "Set tmp->height to " << tmp->height << std::endl;

    nd = tmp;

    // DEBUG: // std::cout << "Set nd to " << tmp->data.first << std::endl;
    // DEBUG: // std::cout << "Result: nd = " << nd->data.first << ", left = " << nd->left->data.first << ", right = " << nd->right->data.first << std::endl;
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

/*-----------------------------------
    Recursive call for search
-------------------------------------*/

template <class T>
node<T>* rbt<T>::search(int key, node<T> *nd)
{
    if(nd == nullptr) return nullptr;
    if(key == nd->data.first) return nd;
    if(key > nd->data.first)
    {
        return search(key, nd->right);
    }
    else
    {
        return search(key, nd->left);
    }
}

/*-----------------------------------
    Print node values between
    traversing left and right trees
-------------------------------------*/

template <class T>
void rbt<T>::inorder()
{
    if(root == nullptr) return;
    inorder(root);
}

/*-----------------------------------
    Recursive call for inorder
-------------------------------------*/

template <class T>
void rbt<T>::inorder(node<T>* nd)
{
    if(nd == nullptr) return;
    inorder(nd->left);
    std::cout << nd->data.first;
    if(nd -> color == BLACK)
    {
        std::cout <<" "<< "color is black" <<std::endl;
    }
    else
    {
        std::cout <<" "<< "color is red" <<std::endl;
    }
    inorder(nd->right);
}

/*-----------------------------------
    Print node values in level order
-------------------------------------*/

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

/*--------------------------
    Get next node
----------------------------*/

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


    /*node<T> *current = nd;
    node<T> *tmp = nd;

    if(current->right != nullptr)
    {
        while(current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
    
    current = current->parent;

    while(current != nullptr && tmp == current->right)
    {
        tmp = current;
        current = current->parent;
    }*/

    /*if(nd == nullptr) return nd;

    node<T> *current = nd;

    if(nd->right != nullptr)
    {
        current = nd->right;
        while(current->right != nullptr)
        {
            current = current->right;
        }
        return current;
    }

    current = nd->parent;
    while(current != nullptr && nd == current->right)
    {
        nd = current;
        current = current->parent;
    }
    return current;*/
}

/*-------------------------------------
    Delete node associated with key
---------------------------------------*/

template <class T>
void rbt<T>::deleteKey(int key)
{
    node<T> *result = search(key);

    // Perhaps return boolean for QT use?
    if(result == nullptr)
    {
        std::cout << "Cannot delete non-existent key " << key << std::endl;
        return;
    }
    deleteKey(result);
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

/*-----------------------------------
    Turn sorted array into RBT, vice-versa
-------------------------------------*/

template <class T>
rbt<T> rbt<T>::sortedArrayToTree(std::vector<std::pair<int, T> > items)
{
    rbt<T> tree;
    unsigned int size = items.size();
    for(int i = 0; i < size; i++)
    {
        tree.insert(items[i]);
    }
    return tree;
}

template <class T>
std::vector<std::pair<int, T> > rbt<T>::treeToSortedArray() {
    std::clog << "this->size: " << this->size << std::endl;
    std::clog << "vct size: " << this->items.size() << std::endl;
    std::sort(this->items.begin(), this->items.end());
    return this->items;
}