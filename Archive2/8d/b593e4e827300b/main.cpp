#include <iostream>
#include <algorithm>


int main() {

   int *a = new int[5];
   int  b[] = {1, 2, 3, 4, 5};
   std::copy(b, b + 5, a);
   for(std::size_t i(0); i < 5; ++i) std::cout << a[i] << " ";
   std::cout << std::endl;

    return 0;
}