#include "rbt.h"
#include <vector>
#include <queue>

int main()
{
  /*---------------------------------
    RBT insert and inorder test
    -----------------------------------*/

  rbt<int> tree;
  std::vector<int> nums = { -12, 1, 6, 8};

  for(auto itr : nums)
    {
      tree.insert(std::make_pair(itr, itr));
      std::clog << "\nInserting " << itr << ", print: " << std::endl;
      tree.printBreadthFirst();
    }

  std::clog << "\nFinal print: " << std::endl;

  tree.printBreadthFirst();

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
    getNodeBreadthTest
  -------------------------*/

  std::queue<node<int>* > myNodes = tree.getNodeBreadthFirst();
  int tHeight = 0;
  for(int i = 0;i<tree.getSize();i++)
    {
      tHeight = myNodes.front() -> height;
      std::cout<< tHeight <<std::endl;
      myNodes.pop();
    }


    
  /*------------------------
    Delete Key Tests
    --------------------------*/

	std::clog << std::endl;

    tree.printBreadthFirst();

    std::clog << "\nDeleting 4:\n" << std::endl;
    
    tree.deleteKey(4);

    tree.printBreadthFirst();
    
    std::clog << "\nDeleting 24:\n" << std::endl;

    tree.deleteKey(24);
    
    tree.printBreadthFirst();

    /*std::clog << "\nDeleting 8:\n" << std::endl;

    tree.deleteKey(8);
    
    tree.printBreadthFirst();

    std::clog << "\nDeleting 9:\n" << std::endl;

    tree.deleteKey(9);
    
    tree.printBreadthFirst();

    std::clog << "\nDeleting 10:\n" << std::endl;

    tree.deleteKey(10);
    
    tree.printBreadthFirst();*/

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

    rbt<int> newTree = tree.sortedVectorToTree(vct);
    newTree.inorder();*/

  return 0;
}
