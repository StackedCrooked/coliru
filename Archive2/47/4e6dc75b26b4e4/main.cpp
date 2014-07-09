#include <iostream>
#include <numeric>
#include <iterator>

int main()
{
   int sum = 0;
   for(auto i : {1,2,3,4}) {
       sum += i;
   }
   std::cout << sum << '\n';
   
   auto arr = {1,2,3,4};
   std::cout << std::accumulate(std::begin(arr), std::end(arr), 0) << '\n';
}
