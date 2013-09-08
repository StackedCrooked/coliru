#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    
    auto distance = std::distance( begin(v), end(v) );
 
    std::cout << distance << '\n';
}