#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main()
{
    std::vector<std::unique_ptr<int>> v;
    std::vector<std::unique_ptr<int>> p = v;
}
