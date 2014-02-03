#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v1 {1,2,3};
    std::vector<int> v2 {4,5,6};
    for (auto i : v1) {
       for (auto j : v2) {
          std::cout << i << ',' << j << '\n';
       }
    }
}