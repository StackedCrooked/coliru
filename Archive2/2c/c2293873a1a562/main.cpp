#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v { 1,2,3 };
    for (auto it = begin(v); it != end(v); ++it)
    {
        std::cout << *it << " ";
    }
}