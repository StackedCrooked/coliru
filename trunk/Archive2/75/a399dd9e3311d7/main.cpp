#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto it = v.begin();
 
    auto nx = std::next(it, 2);
 
    std::cout << *it << ' ' << *nx << '\n';
}