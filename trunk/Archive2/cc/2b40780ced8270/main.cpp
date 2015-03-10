#include <iostream>

int main() {
    
   long a = 3;
   
   auto i = reinterpret_cast<std::intptr_t>(&a);
   auto j = reinterpret_cast<long*>(i);
   auto k = reinterpret_cast<void*>(i);
   auto b = &a == j;
   auto b2 = (void*)(&a) == k;
   
   std::cout << i << " " << j << " " << k << " " << b << " " << b2 << std::endl;
   
    return 0;
}