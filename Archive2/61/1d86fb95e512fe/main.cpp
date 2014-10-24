#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<std::vector<int>> v{10, std::vector<int>(10)};
    std::cout << v.size() << std::endl;
    for (auto e : v)
        std::cout << e.size() << " ";
}
