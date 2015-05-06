#include "rbt.h"
#include <queue>

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
        // DEBUG: // std::cout << nd->data.first << ", Height: " << nd->height << ", Bfactor: " << this->balanceFactor(nd) << std::endl;
    }
    else
    {
        insert(root, item);
    }
}

/*-----------------------------------
    Recursive call for insert
-------------------------------------*/

template <class T>
void rbt<T>::insert(node<T> *nd, std::pair<int, T> item)
{
    node<T>* newNode = new node<T>(item);
    if(item.first > nd->data.first)
    {
        if(nd->right == nullptr)
        {
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
            nd->left = newNode;
            newNode->parent = nd;
        }
        else
        {
            insert(nd->left, item);
        }
    }

    inOrderColor();
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
        std::cout << front->data.first << std::endl;
        nodeSet.pop();
    }
    std::cout << std::endl;
}

/*-----------------------------------
    Turn sorted array into RBT
-------------------------------------*/

template <class T>
rbt<T>* rbt<T>::sortedArray(std::pair<int, T> items[])
{
    /*  Note: Are we inserting elements in the sorted
        array to the RBT or are we extracting elements
        from the RBT and returning a sorted array? */

    /*rbt<T> tree;
    unsigned int size = items.size();
    for(int i = 0; i < size; i++)
    {
        tree.insert(items[i]);
    }
    return tree;*/
}

/*-----------------------------------
    Delete node associated with key
-------------------------------------*/

template <class T>
void rbt<T>::deleteKey(int key){/* To Do */}


/*-----------------------------------
  Change colors of nodes by RBT properties
-------------------------------------*/
template <class T>
void rbt<T>::inOrderColor()
{
    if(root == nullptr)
        {return;}
    inOrderColor(root);
}

/*-----------------------------------
  Recursive inOrderColor
-------------------------------------*/

template <class T>
void rbt<T>::inOrderColor(node<T> *nd)
{
    if(nd == nullptr) return;
    inOrderColor(nd->left);
    childCheck(nd);
    //pathCheck(nd);
    inOrderColor(nd->right);
    
}

/*-----------------------------------
  Makes sure colors are correct
-------------------------------------*/
template <class T>
  void rbt<T>::childCheck(node<T> *nd) 
  {   
    if(nd == nullptr)
        {return;}
    if(nd != root || nd -> parent -> color != BLACK)
    {
        if(nd -> parent -> parent != nullptr)
        {
            node<T> *grandPa = nd -> parent -> parent;
            node<T> *dad = nd -> parent;
            if(grandPa -> left  == nd -> parent)
            {
            // if uncle red 
                if(grandPa -> right -> color == RED)
                {
                    nd -> parent -> color = BLACK;
                    grandPa -> right -> color = BLACK;
                    grandPa -> color = RED;
                    nd = grandPa;
                    childCheck(nd);
                }
            // if uncle black
                else
                {
                    if(dad -> left == nd)
                    {
                        leftLeft(grandPa, dad);  
                    }
                    else
                    {
                        leftRight(grandPa, dad);
                    }
                }
            }
            else if(grandPa -> right  == nd -> parent)
            {
            // if uncle red 
                if(grandPa -> left -> color == RED)
                {
                    nd -> parent -> color = BLACK;
                    grandPa -> left -> color = BLACK;
                    grandPa -> color = RED;
                    nd = grandPa;
                    childCheck(nd);
                }
             // if uncle black
                else
                {
                    if(dad -> right == nd)
                    {
                        rightRight(grandPa, dad);  
                    }
                    else
                    {
                        rightLeft(grandPa, dad);
                    }
                }
            }  
        }
    }
    else if(nd == root)
    {
       nd ->color = BLACK;
    }
}


/*-----------------------------------
  Four cases for uncle node is black
-------------------------------------*/

/*---------------------------------------------------------
  I. nd's parent is left nd's grandPa and nd is left parent
---------------------------------------------------------*/
template <class T>
void rbt<T>::leftLeft(node<T> *grandPa, node<T> *dad)
{
    node<T> *temp = grandPa;
    rotateRight(grandPa);
    grandPa -> color = dad -> color;
    dad -> color = temp ->color;
}

/*---------------------------------------------------------
  II. nd's parent is left nd's grandPa and nd is right parent
---------------------------------------------------------*/

template <class T>
void rbt<T>::leftRight(node<T> *grandPa, node<T> *dad)
{
    rotateLeft(dad);
    leftLeft(grandPa, dad);
}

/*---------------------------------------------------------
  III. nd's parent is right nd's grandPa and nd is right parent
---------------------------------------------------------*/

template <class T>
void rbt<T>::rightRight(node<T> *grandPa, node<T> *dad)

{
    node<T> *temp = grandPa;
    rotateLeft(grandPa);
    grandPa -> color = dad -> color;
    dad -> color = temp ->color;   
}

/*---------------------------------------------------------
  IV. nd's parent is right nd's grandPa and nd is left parent
---------------------------------------------------------*/

template <class T>
void rbt<T>::rightLeft(node<T> *grandPa, node<T> *dad)
{
    rotateRight(dad);
    rightRight(grandPa, dad);
}




