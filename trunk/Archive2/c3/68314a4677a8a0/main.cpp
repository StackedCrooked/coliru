#include <iostream>
#include <vector>
 
int main() 
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for ( int i : v) // access by reference (const allowed)
    {
        std::cout << i << ' ';
        i = i*2;
    }
 
    std::cout << '\n';
 
    for (auto i : v) // compiler uses type inference to determine the right type
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (int i : v) // access by value as well
        std::cout << i << ' ';
 
    std::cout << '\n';
}