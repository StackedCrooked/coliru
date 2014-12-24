#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
int main()
{
    std::vector<int> v{1,2,3,4,7};
    std::list<int> l{-1,-2,-3};
    
    std::copy(v.begin(), v.end(), // may be simplified with std::inserter
              std::insert_iterator<std::list<int>>(l, ++l.begin()));
    for(int n : l)
        std::cout << n << ' ';
    std::cout << '\n';
}