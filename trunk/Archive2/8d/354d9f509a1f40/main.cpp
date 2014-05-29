#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <iterator>
 
int main()
{
    std::list<std::string> s{"one", "two", "three"};
 
    std::vector<std::string> v1(s.begin(), s.end()); // copy
 
    std::vector<std::string> v2(std::make_move_iterator(s.begin()),
                                std::make_move_iterator(s.end())); // move
 
    std::cout << "v1 now holds: ";
    for (auto str : v1)
            std::cout << "\"" << str << "\" ";
    std::cout << "\nv2 now holds: ";
    for (auto str : v2)
            std::cout << "\"" << str << "\" ";
    std::cout << "\noriginal list now holds: ";
    for (auto str : s)
            std::cout << "\"" << str << "\" ";
    std::cout << '\n';
}