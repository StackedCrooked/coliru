#include <iostream>   
#include <valarray>  


int main() {

std::valarray<int> v1 = {1,2,3};

std::valarray<int> v2(3 * v1.size());

std::size_t index = 0;
std::for_each(std::begin(v1), std::end(v1), [&](int n) { for(auto i = 0 ; i < 3 ; ++i) v2[index++] = n; } );

for(auto i : v2)
   std::cout << i << ' ';

}