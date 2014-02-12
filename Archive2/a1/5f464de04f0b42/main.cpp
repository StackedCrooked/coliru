#include <iostream>
#include <vector>
#include <map>


std::map<int, std::vector<int>> foo()
{
    std::map<int, std::vector<int>> data;
    data[7] = { 0, 1, 2 };
    return data;
}

int main()
{
    for (const auto& i : foo()[7])
        std::cout << i << std::endl;
}