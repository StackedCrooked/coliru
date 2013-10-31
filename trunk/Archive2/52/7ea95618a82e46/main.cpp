#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5,6};
    std::list<int> l = {-1, -2, -3, -4, -5};
 
    std::swap_ranges(v.begin(), v.begin()+3, l.begin());
 
    for(int n : v)
       std::cout << n << ' ';
    std::cout << '\n';
    for(int n : l)
       std::cout << n << ' ';
    std::cout << '\n';
}