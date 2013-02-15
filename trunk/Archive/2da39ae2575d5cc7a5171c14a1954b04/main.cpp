#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(10, 1);
    for (auto i = begin(v), e = end(v); i != e; ++i)
    {
        std::cout << *i << " ";
    }
}