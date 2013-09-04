#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
    std::list<const char*> lict{"Hello", "World"};
    std::vector<std::string> vec(lict.begin(), lict.end());
    for(const auto& elem : lict) std::cout << elem << std::endl;
    for(const auto& elem : vec) std::cout << elem << std::endl;
}