#include <iostream>
#include <iterator>
#include <list>
 
int main() 
{
    std::list<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
 
    size_t distance = std::distance(v.end(), v.begin());
 
    std::cout << distance << '\n';
}
