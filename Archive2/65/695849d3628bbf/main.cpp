#include <iterator>
#include <iostream>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/copy.hpp>

using namespace std;
using namespace boost::adaptors;

template<typename T, size_t N>
void split(T (&input)[N], size_t block_size)
{
   for (size_t i(0); i <= N-block_size; i += block_size)
   {
       cout << "{ ";
       boost::copy(input | sliced(i, i+block_size),
           std::ostream_iterator<int>(std::cout, " "));
       cout << "}\n"; 
   }
}


int main()
{
    int A[] = {1, 2, 3, 4};
    split(A, 2); 
}
