#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 30, 10, 4 };
 
    auto distance = std::distance(v.begin(), v.end());
 
    std::cout << distance << '\n';
}