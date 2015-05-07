#include "rbt.h"
#include <vector>

int main()
{
    /*---------------------------------
        RBT insert and inorder test
    -----------------------------------*/

    rbt<int> tree;
    std::vector<int> nums = { 7, 3, 9, -3, 10 };

    for(auto itr : nums)
    {
        tree.insert(std::make_pair(itr, itr));
        std::clog << "\nInserting " << itr << ", in order print: " << std::endl;
        tree.inorder();
    }

    tree.inorder();

    std::clog << std::endl;

    /*---------------------
        RBT search test
    -----------------------*/

    // Add in new nums for testing failed searches
    nums.push_back(0);
    nums.push_back(1);
    nums.insert(nums.begin(), 2);
    nums.insert(nums.begin(), 5);

    for(auto itr : nums)
    {
        std::clog << "Searching for " << itr;
        if(itr >= 0 && itr < 10) std::clog << "\t";
        std::clog << "\t...\t";
        node<int> *nd = tree.search(itr);
        if(nd != nullptr)
        {
            std::clog << "found it!" << std::endl;
        }
        else
        {
            std::clog << "not found!" << std::endl;
        }
    }

    /*------------------------
        Delete Key Tests
    --------------------------*/

    std::clog << std::endl;

    tree.inorder();
    std::clog << std::endl;
    
    tree.deleteKey(3);
    
    tree.inorder();

    /*------------------------
        Sorted Array Tests
    --------------------------*/

    /*std::vector<std::pair<int, int> > vct = tree.treeToSortedArray();
    unsigned int treeSize = tree.getSize();
    for(int i = 0; i < treeSize; i++)
    {
        std::clog << vct[i].second << std::endl;
    }

    vct.push_back(std::make_pair(15, 15));

    rbt<int> newTree = tree.sortedArrayToTree(vct);
    newTree.inorder();*/

    return 0;
}
