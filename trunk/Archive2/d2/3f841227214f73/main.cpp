#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto it = v.end();
 
    auto pv = std::prev(it);
 
    std::cout << *pv << '\n';
}