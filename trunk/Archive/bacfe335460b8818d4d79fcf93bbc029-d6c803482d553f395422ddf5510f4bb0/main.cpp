#include <vector>
#include <iostream>
 
 
int main( )
{
    std::vector<int> c{0, 1, 2, 4, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    c.erase(c.begin());
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    c.erase(c.begin()+3, c.begin()+5);
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}