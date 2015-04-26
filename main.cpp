#include "rbt.h"
#include <vector>

int main()
{
    /*---------------------------------
        RBT insert and inorder test
    -----------------------------------*/

    rbt<int> tree;
    std::vector<int> nums = { 7, 3, 9, -3, 10 };

    for(auto itr: nums)
    {
        tree.inorder();
        std::clog << "\nInserting " << itr << ", in order print: " << std::endl;
        tree.insert(std::make_pair(itr, itr));
    }

    tree.inorder();

    std::clog << std::endl;

    /*---------------------
        RBT search test
    -----------------------*/

    // Add in new nums for testing failed searches
    nums.push_back(std::make_pair(0, 0));
    nums.push_back(std::make_pair(1, 1));
    nums.insert(nums.begin(), std::make_pair(2, 2));
    nums.insert(nums.begin(), std::make_pair(4, 4));

    for(auto itr : nums)
    {
        std::clog << "Searching for " << itr << "\t...\t";
        node* nd = tree.search(itr);
        if(nd != nullptr)
        {
            std::clog << "found it!" << std::endl;
        }
        else
        {
            std::clog << "not found!" << std::endl;
        }
    }

    return 0;
}
