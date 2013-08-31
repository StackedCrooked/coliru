#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

int main()
{
   std::string big_data[] = { "hello", "world", "I", "need", "to", "get", "the", "median", "index" };    

   auto const N = std::distance(std::begin(big_data), std::end(big_data));
   auto const M = (N - 1) / 2; // 9 elements, median is 4th element in sorted array
   
   std::vector<int> indices;
   auto value = 0;
   std::generate_n(std::back_inserter(indices), N, [&](){ return value++; });
   
   std::nth_element(indices.begin(), indices.begin() + M, indices.end(), [&](int lhs, int rhs){ 
       return big_data[lhs] < big_data[rhs]; 
   });
   std::cout << indices[M] << ":" << big_data[indices[M]] << "\n";
   
   // check, sort input array
   std::sort(std::begin(big_data), std::end(big_data));
   std::cout << M << ":" << big_data[M] << "\n";
}