#include <list>
#include <iostream>
#include <iterator>
 
int main( )
{
    std::list<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    c.erase(c.begin());
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    std::list<int>::iterator range_begin = c.begin();
    std::list<int>::iterator range_end = c.begin();
    std::advance(range_begin,2);
    std::advance(range_end,5);
 
    c.erase(range_begin, range_end);
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}