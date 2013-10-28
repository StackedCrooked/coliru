#include <iostream>
#include <vector>

#define foreach(type, container) \
for(type::iterator it = container.begin(); it != container.end(); it++)

int main()
{
    std::vector<int> roba;
    roba.push_back(10);
    roba.push_back(20);
    roba.push_back(30);
    
    foreach(std::vector<int>, roba)
        std::cout << *it << std::endl;
    
    return 0;
}