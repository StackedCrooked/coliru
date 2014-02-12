#include <string>
#include <iostream>
#include <vector>
#include <map>

std::map<int, std::vector<std::string>> foo()
{
    std::map<int,std::vector<std::string>> m;
    for (int i=0; i<100; ++i)
    {
        m[42].push_back(std::to_string(i));
    }
    return m;
}


int main()
{
    for (const std::string& i : foo()[42])
    {
        std::cout << i << std::endl;
    }
}