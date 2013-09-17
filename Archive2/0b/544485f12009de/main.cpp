#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
 
int main()
{
    std::vector<int> v;
    std::generate_n(std::back_insert_iterator<std::vector<int>>(v), // can be simplified
                    10, [](){ return std::rand() % 10; });        // with std::back_inserter
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}