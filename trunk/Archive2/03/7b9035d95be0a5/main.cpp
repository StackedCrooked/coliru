#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
 
int main()
{
    std::vector<std::string> src{"foo", "bar", "baz"};
    std::vector<std::string> dest(src.size() * 2);
 
    std::cout << "src: ";
    for (const auto &s : src)
    {
        std::cout << s << ',';
    }   
    std::cout << "\ndest: ";
    for (const auto &s : dest)
    {
        std::cout << s << ',';
    }   
    std::cout << '\n' << '\n' << "after move backward" << '\n';
 
    std::move_backward(src.begin(), src.end(), dest.end());
 
    std::cout << "src: ";                                                       
    for (const auto &s : src)
    {
        std::cout << s << ',';
    }   
    std::cout << "\ndest: ";
    for (const auto &s : dest)
    {
        std::cout << s << ',';
    }   
    std::cout << '\n';
}