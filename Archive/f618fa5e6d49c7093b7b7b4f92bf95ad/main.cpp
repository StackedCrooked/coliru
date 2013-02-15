#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(10, 1);
    for (auto it = begin(v), e = end(v); it != e; ++it)
    {
        std::cout << *it << " ";
    }
}