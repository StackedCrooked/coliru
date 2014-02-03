#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    const std::size_t N = 5;
    int ar[N];
    std::generate_n(ar, N, std::rand); // Using the C function rand()
 
    std::cout << "ar: ";
    std::copy(ar, ar+N, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}