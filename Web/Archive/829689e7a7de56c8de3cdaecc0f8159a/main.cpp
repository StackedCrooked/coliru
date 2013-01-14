#include <iostream>
#include <algorithm>
#include <functional>
#include <list>

int main()
{
    std::list<int> l{1,2,3,4,5,6,7,8,9,10};
    l.erase(std::remove_if(l.begin(),
                           l.end(),
                           [](int i) { return i%2 == 0; }), 
                           l.end());
    for(auto i : l ) std::cout << i << std::endl;
}
