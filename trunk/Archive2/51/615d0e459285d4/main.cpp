#include <vector>
#include <iostream>
#include <iterator>
 
int main( )
{
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    std::vector<int>::const_iterator bit = c.begin();
    c.erase(bit);
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    std::vector<int>::iterator range_begin = c.begin();
    std::vector<int>::iterator range_end = c.begin();
    std::advance(range_begin,2);
    std::advance(range_end,5);
 
    c.erase(range_begin, range_end);
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}