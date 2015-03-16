#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v{1,2,3};
    std::list<int> l{3,4,5};
    
    for (auto &e: l)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";
    
    std::copy(v.begin(), v.end(), l.begin());
    
    for (auto &e: l)
    {
        std::cout << e << " ";
    }
}