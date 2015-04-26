#include "rbt.h"
#include <vector>

int main()
{
    /*---------------------
        RBT Insert Test
    -----------------------*/

    rbt tree;
    std::vector<double> nums;
    nums.push_back(7.0);
    nums.push_back(3.0);
    nums.push_back(9.0);
    nums.push_back(-3.0);
    nums.push_back(10.0);

    for(auto itr: nums)
    {
        tree.insert(itr);
    }

    tree.inorder();

    return 0;
}
