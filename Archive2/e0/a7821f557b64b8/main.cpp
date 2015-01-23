#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> vec = {"Hello", "World"};
    vec[0][0] = 'h';
    
    for (auto& s : vec) std::cout << s << " ";
    return 0;
}