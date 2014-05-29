#include <set>
#include <cassert>
#include <iostream>
 
int main()
{
  std::set<int> set;
 
  auto result_1 = set.insert(3);
  assert(result_1.first != set.end()); // it's a valid iterator
  assert(*result_1.first == 3);
  if (result_1.second)
    std::cout << "insert done\n";
 
  auto result_2 = set.insert(3);
  assert(result_2.first == result_1.first); // same iterator
  assert(*result_2.first == 3);
  if (!result_2.second)
    std::cout << "no insertion\n";
}