#include <iostream>
#include <array>

int main() {

   std::array<int, 5> a;
   std::array<int, 5> b {{1, 2, 3, 4, 5}};
   a = b;
   for(auto i : a) std::cout << i << " ";
   std::cout << std::endl;

    return 0;
}