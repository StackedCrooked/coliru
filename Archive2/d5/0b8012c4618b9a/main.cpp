#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    // Inserts vector v between -1 and -2 of the list
    std::vector<int> v{1,2,3,4,5};
    std::list<int> l{-1,-2,-3};
    std::copy(v.begin(), v.end(), // may be simplified with std::inserter
              std::insert_iterator<std::list<int>>(l, std::next(l.begin()))); 
    for (int n : l)
        std::cout << n << ' ';
    std::cout << '\n';
}