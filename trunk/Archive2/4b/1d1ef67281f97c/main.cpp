#include <iostream>
#include <list>
 
int main()
{
  std::list<int> x = {1, 2, 2, 3, 3, 2, 1, 1, 2};
 
  std::cout << "contents before:";
  for (auto val : x)
    std::cout << ' ' << val;
  std::cout << '\n';
 
  x.unique();
  std::cout << "contents after unique():";
  for (auto val : x)
    std::cout << ' ' << val;
  std::cout << '\n';
 
  return 0;
}