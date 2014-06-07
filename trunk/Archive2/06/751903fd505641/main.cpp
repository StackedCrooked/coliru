#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 102, 4, 69 };
 
    auto distance = std::distance(v.begin(), v.end());
 
    std::cout << distance << '\n';
}