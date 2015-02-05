#include <iostream>
#include <string>
#include <vector>
#include <memory>

std::vector<std::unique_ptr<int>> blah{
    std::unique_ptr<int>(new int()),
    std::unique_ptr<int>(new int()),
};

int main()
{
}
