#include <vector>
#include <iostream>

class A
{
public:
    std::vector<int> v1{ 12, 1 };
    std::vector<int> v2 = std::vector<int>(12, 1);
};

int main() 
{
  A a;
  for(int i : a.v1) std::cout << i << ' '; std::cout << '\n';
  for(int i : a.v2) std::cout << i << ' '; std::cout << '\n';
}
