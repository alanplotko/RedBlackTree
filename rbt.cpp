#include "rbt.h"
#include <queue>

/*-----------------------------------
    RBT tree destructor starting
    at the root node
-------------------------------------*/

rbt::~rbt() { cleanRbt(root); }

/*-----------------------------------
    Called by the destructor;
    destroys all nodes in RBT tree
-------------------------------------*/

void rbt::cleanRbt(node* nd)
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
    Insert double into RBT tree
-------------------------------------*/

void rbt::insert(double dta)
{
    if(root == nullptr)
    {
        node* nd = new node(dta);
        root = nd;
        // DEBUG: // std::cout << nd->data << ", Height: " << nd->height << ", Bfactor: " << this->balanceFactor(nd) << std::endl;
    }
    else
    {
        insert(root, dta);
    }
}

/*-----------------------------------
    Recursive call for insert
-------------------------------------*/

void rbt::insert(node *nd, double dta)
{
    if(dta > nd->data)
    {
        if(nd->right == nullptr)
        {
            node* newNode = new node(dta);
            nd->right = newNode;
            newNode->parent = nd;
        }
        else
        {
            insert(nd->right, dta);
        }
    }
    else
    {
        if(nd->left == nullptr)
        {
            node* newNode = new node(dta);
            nd->left = newNode;
            newNode->parent = nd;
        }
        else
        {
            insert(nd->left, dta);
        }
    }
  
    // Recalculate heights
    maxHeight(nd);

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
    }
}

/*-----------------------------------
    Get balance factor for rotations
-------------------------------------*/

int rbt::balanceFactor(node *nd)
{
    int left = (nd->left == nullptr ? 0 : nd->left->height);
    int right = (nd->right == nullptr ? 0 : nd->right->height);
    return right - left;
}

/*-----------------------------------
    Set node's height to the larger
    height of its child nodes, plus 1
-------------------------------------*/

void rbt::maxHeight(node *nd)
{
    int left = (nd->left == nullptr ? 0 : nd->left->height);
    int right = (nd->right == nullptr ? 0 : nd->right->height);
    nd->height = std::max(left, right) + 1;
}

/*-----------------------------------
    Rotate RBT tree to the left
-------------------------------------*/

void rbt::rotateLeft(node *nd)
{
    // DEBUG: // std::cout << "Working left with " << nd->data << std::endl;
    node *tmp = nd->right;
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

void rbt::rotateRight(node *nd)
{
    // DEBUG: // std::cout << "Working right with " << nd->data << std::endl;

    node* tmp = nd->left;

    // DEBUG: // std::cout << "Set tmp to " << nd->left->data << std::endl;

    tmp->parent = nd->parent;

    // DEBUG: // double test = (nd->parent == nullptr ? 0 : nd->parent->data);
    // DEBUG: // std::cout << "Set tmp->parent to " << test << std::endl;

    nd->left = tmp->right;

    // DEBUG: // std::cout << "Set nd->left to " << tmp->right << std::endl;

    if(nd->left != nullptr)
    {
    // DEBUG: // std::cout << "Set nd->left->parent to " << nd->data << std::endl;
    nd->left->parent = nd;
    }

    tmp->right = nd;

    // DEBUG: // std::cout << "Set tmp->right to " << nd->data << std::endl;

    nd->parent = tmp;

    // DEBUG: // std::cout << "Set nd->parent to " << tmp->data << std::endl;

    // DEBUG: // double test2 = (tmp->parent == nullptr ? 0 : tmp->parent->data);
    // DEBUG: // std::cout << "tmp->parent is " << test2 << std::endl;

    if (tmp->parent != nullptr)
    {
        if (tmp->parent->right == nd)
        {
            tmp->parent->right = tmp;
            // DEBUG: // std::cout << "Set tmp->parent->right to " << tmp->data << std::endl;
        }
        else
        {
            tmp->parent->left = tmp;
            // DEBUG: // std::cout << "Set tmp->parent->left to " << tmp->data << std::endl;
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

    // DEBUG: // std::cout << "Set nd to " << tmp->data << std::endl;
    // DEBUG: // std::cout << "Result: nd = " << nd->data << ", left = " << nd->left->data << ", right = " << nd->right->data << std::endl;
}

/*-----------------------------------
    Find and return a node by value
-------------------------------------*/

node* rbt::find(double dta)
{
    if(root == nullptr) return nullptr;
    return find(root, dta);
}

/*-----------------------------------
    Recursive call for find
-------------------------------------*/

node* rbt::find(node* nd, double dta)
{
    if(nd == nullptr) return nullptr;
    if(dta == nd->data) return nd;
    if(dta > nd->data)
    {
        return find(nd->right, dta);
    }
    else
    {
        return find(nd->left, dta);
    }
}

/*-----------------------------------
    Print node values between
    traversing left and right trees
-------------------------------------*/

void rbt::inorder()
{
    if(root == nullptr) return;
    inorder(root);
}

/*-----------------------------------
    Recursive call for inorder
-------------------------------------*/

void rbt::inorder(node* nd)
{
    if(nd == nullptr) return;
    inorder(nd->left);
    std::cout << nd->data << std::endl;
    inorder(nd->right);
}

/*-----------------------------------
    Print node values in level order
-------------------------------------*/

void rbt::printBreadthFirst()
{
    if(root == nullptr) return;
    std::queue<node*> nodeSet;
    nodeSet.push(root);
    while(!nodeSet.empty())
    {
        node* front = nodeSet.front();
        if(front->left != nullptr)
        {
            nodeSet.push(front->left);
        }
        if(front->right != nullptr)
        {
            nodeSet.push(front->right);
        }
        std::cout << front->data << std::endl;
        nodeSet.pop();
    }
    std::cout << std::endl;
}