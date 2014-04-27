#include <set>
#include <iostream>

int main()
{
   std::set<int> notAList{1,2,3,4,5};
   
   for (auto el : notAList)
      std::cout << el << ' ';
   std::cout << '\n';
   
   notAList.erase(4);
   
   for (auto el : notAList)
      std::cout << el << ' ';
   std::cout << '\n';
}

// 1 2 3 4 5
// 1 2 3 5