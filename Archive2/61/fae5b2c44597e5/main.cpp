#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> v { "lol", "lol2", "lol3" };
    for(const std::string& s: v)
    {
        std::cout << s << std::endl;
    }
    
    return 0;
}