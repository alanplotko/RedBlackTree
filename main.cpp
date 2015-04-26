#include "rbt.h"
#include <vector>

int main()
{
    /*---------------------------------
        RBT insert and inorder test
    -----------------------------------*/

    rbt tree;
    std::vector<double> nums = { 7.2, 3.1, 9.8, -3.2, 10.9 };

    for(auto itr: nums)
    {
        tree.inorder();
        std::clog << "\nInserting " << itr << ", in order print: " << std::endl;
        tree.insert(itr);
    }

    tree.inorder();

    std::clog << std::endl;

    /*---------------------
        RBT search test
    -----------------------*/

    // Add in new nums for testing failed searches
    nums.push_back(0.5);
    nums.push_back(1.9);
    nums.insert(nums.begin(), 2.3);
    nums.insert(nums.begin(), 4.5);

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
