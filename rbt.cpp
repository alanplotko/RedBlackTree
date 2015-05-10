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
void rbt<T>::cleanRbt()
{
    cleanRbt(root);
    
    // Reset size and sorted vector
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
        insert(root, item);
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
void rbt<T>::insert(node<T> *nd, std::pair<int, T> item)
{
    // Case 1: item weight >= current node weight
    if(item.first >= nd->data.first)
    {
        // Case 1a: found open space for insert
        if(nd->right == nullptr)
        {
            node<T> *newNode = new node<T>(item);
            nd->right = newNode;
            newNode->parent = nd;

            // Recolor tree based on new node's properties
            insertRecolor(newNode);
            return;
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
            node<T> *newNode = new node<T>(item);
            nd->left = newNode;
            newNode->parent = nd;

            // Recolor tree based on new node's properties
            insertRecolor(newNode);
            return;
        }
        // Case 2b: current space contains node;
        //          keep moving to the left
        else
        {
            insert(nd->left, item);
        }
    }
}

/*---------------------------------------
    Examine the newly inserted node's
    properties and recolor the tree
-----------------------------------------*/

template <class T>
void rbt<T>::insertRecolor(node<T> *nd)
{
    // Recoloring process ends if node is root or node's parent is red
    while(nd != root && nd->parent != nullptr && nd->parent->color == RED)
    {
        /*  End recoloring process early if node does not have a grandpa.
            The tree is still underdeveloped to need any recoloring,
            since we don't have an uncle without a grandpa. */
        if(nd->parent->parent == nullptr) return;
        
        node<T> *uncle;

        // Determine which side the uncle node is on
        if(nd->parent == nd->parent->parent->left)
        {
            uncle = nd->parent->parent->right;
        }
        else
        {
            uncle = nd->parent->parent->left;            
        }

        // Case 1: uncle node is red
        if(uncle != nullptr && uncle->color == RED)
        {
            nd->parent->color = BLACK;
            uncle->color = BLACK;
            nd->parent->parent->color = RED;
            nd = nd->parent->parent;
        }
        // Case 2: uncle node is black
        else
        {
            // Case 2a: uncle on right
            if(uncle != nullptr && uncle == nd->parent->parent->right)
            {
                /*  Left-Right Case:
                    Node's parent on grandpa's left;
                    Node is on parent's right */
                if(nd == nd->parent->right)
                {
                    nd = nd->parent;
                    rotateLeft(nd);
                }

                /*  Left-Left Case:
                    Node's parent on grandpa's left;
                    Node is on parent's left */

                // Swap parent's and grandpa's colors
                type tmp = nd->parent->color;
                nd->parent->color = nd->parent->parent->color;
                nd->parent->parent->color = tmp;

                rotateRight(nd->parent->parent);
            }
            // Case 2b: uncle on left
            else {
                if(nd == nd->parent->left)
                {
                    /*  Right-Left Case:
                        Node's parent on grandpa's right;
                        Node is on parent's left */
                    nd = nd->parent;
                    rotateRight(nd);
                }

                /*  Right-Right Case:
                    Node's parent on grandpa's right;
                    Node is on parent's right */

                // Swap parent's and grandpa's colors
                type tmp = nd->parent->color;
                nd->parent->color = nd->parent->parent->color;
                nd->parent->parent->color = tmp;

                rotateLeft(nd->parent->parent);
            }
        }
    }

    // Root node must always be black
    root->color = BLACK;
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

/*----------------------------
    Search and return node
    pointer by key
------------------------------*/

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
    std::cout << nd->data.second << std::endl;
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
            test = front->parent->data.second;
        }
        std::cout << front->data.second << ": " << front->color << " (" << test << ")" << std::endl;
        nodeSet.pop();
    }
    std::cout << std::endl;
}

/*--------------------------
    Return size of tree
----------------------------*/

template <class T>
int rbt<T>::getSize() { return this->size; }

/*--------------------------------------
    Get largest node in same subtree
----------------------------------------*/

template <class T>
node<T>* rbt<T>::getLargestNode(node<T> *nd)
{
    node<T> *current = nd;

    // Largest node is rightmost node of the subtree
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
    // Confirm node wth key exists
    node<T> *result = search(key);
    if(result == nullptr) return false;

    // Delete node with key
    deleteKey(result);

    // Delete corresponding item from vector
    std::pair<int, int> pair = std::make_pair(key, key);
    items.erase(std::remove(items.begin(), items.end(), pair), items.end());

    // Update size of tree
    size--;

    return true;
}

template <class T>
void rbt<T>::deleteKey(node<T> *nd)
{
    // tmp is the node we want to delete
    node<T> *tmp = nd;

    // tmp has 2 children
    if(tmp->left != nullptr && tmp->right != nullptr)
    {
        /*  Largest node on tmp's left subtree has
            largest value below tmp */
        tmp = getLargestNode(tmp->left);

        // Replace deleted node with tmp
        nd->data = tmp->data;
    }

    /*  Check for remaining children
        - tmp originally had 2 children:
            In this case, the largest node before tmp
            replaced the node we want to delete. Now,
            we want to delete that largest node instead,
            to avoid have a duplicate node in the tree.
        - tmp originally had at most 1 child:
            We are still trying to delete the original node,
            so we want to determine the child that will take
            its place. */
    node<T> *remainingChild;

    if(tmp->left != nullptr)
    {
        remainingChild = tmp->left;
    }
    else if(tmp->right != nullptr)
    {
        remainingChild = tmp->right;
    }
    else
    {
        remainingChild = nullptr;
    }
    
    // Case 1: one child node remains
    if(remainingChild != nullptr)
    {
        /*  Case 1a: tmp is the root,
            so to replace it, we need
            to set a new root */
        if(tmp == root)
        {
            root = remainingChild;
            remainingChild->parent = nullptr;
        }
        // Case 1b: tmp is on the left
        else if(tmp == tmp->parent->left)
        {
            tmp->parent->left = remainingChild;
            remainingChild->parent = tmp->parent;
        }
        // Case 1c: tmp is on the right
        else
        {
            tmp->parent->right = remainingChild;
            remainingChild->parent = tmp->parent;
        }

        /*  If the tmp node is black, then the tree is not
            a valid rbt, and needs to be recolored */
        if(getColor(tmp) == BLACK) deleteRecolor(tmp);

        /*  Before deleting tmp, we want to remove
            the association its parent has to tmp */
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
        return;
    }

    // Case 2: tree is now empty
    else if(tmp == root)
    {
        root = nullptr;
        return;
    }

    // Case 3: 0 child nodes remain
    else
    {
        /*  If the tmp node is black, then the tree is not
            a valid rbt, and needs to be recolored */
        if(getColor(tmp) == BLACK) deleteRecolor(tmp);

        /*  Before deleting tmp, we want to remove
            the association its parent has to tmp */
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
        return;
    }
}

/*----------------------
    Get node's color
------------------------*/

template <class T>
type rbt<T>::getColor(node<T> *nd)
{
    // "nullptr" is considered as a black node
    if(nd == nullptr) return BLACK;
    return nd->color;
}

/*-------------------------------------
    Examine the deleted node's
    properties and recolor the tree
---------------------------------------*/

template <class T>
void rbt<T>::deleteRecolor(node<T> *nd)
{
    while(nd != root && nd->parent != nullptr && getColor(nd) == BLACK)
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
        else if(nd == nd->parent->right)
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
void rbt<T>::sortedVectorToTree(std::vector<std::pair<int, T> > items)
{
    cleanRbt();
    unsigned int size = items.size();
    for(unsigned int i = 0; i < size; i++)
    {
        insert(items[i]);
    }
}

template <class T>
std::vector<std::pair<int, T> > rbt<T>::treeToSortedVector()
{
    /*  Pairs have their own sorting algorithm implemented
        by default using their keys for comparisons */
    std::sort(this->items.begin(), this->items.end());
    return this->items;
}

/*------------------------------
    Get nodes in level order
--------------------------------*/

template<class T>
std::queue<node<T>*> rbt<T>::getNodeBreadthFirst()
{
    std::queue<node<T>*> nodeSet;
    std::queue<node<T>*> retSet;
    if(root == nullptr) return retSet;
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
        retSet.push(nodeSet.front());
        nodeSet.pop();
    }
    return retSet;
}
