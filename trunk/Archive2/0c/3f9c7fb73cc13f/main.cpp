#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    int distance = std::distance(v.begin(), v.end());
 
    std::cout << distance << '\n';
}