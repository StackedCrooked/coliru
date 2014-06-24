#include <iostream>
#include <vector>
#include <algorithm>

int main() {
   std::vector<int> a(5);
   int b[] = {1, 2, 3, 4, 5};
   std::copy(b, b + 5, a.begin());
   for(auto i : a) std::cout << i << " ";
   std::cout << std::endl;

    return 0;
}