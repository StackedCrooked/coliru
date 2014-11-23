#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

template<class OutputIterator, class Size, class Assignable>
void iota_n(OutputIterator first, Size n, Assignable value)
{
   std::generate_n(first, n, [&value]() {
      return value++;
   });
}
 
int main()
{
   const size_t N = 200;
   
   std::vector<int> v;
   v.reserve(N);
   iota_n(std::back_inserter(v), N, 0);
   
   std::random_device rd;
   std::mt19937 g(rd());
   
   std::shuffle(v.begin(), v.end(), g);
   
   std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << "\n";
}