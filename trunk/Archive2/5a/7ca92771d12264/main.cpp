#include <vector>
#include <iostream>

int main()
{
    std::vector<int> a = {1, 2, 3, 4};
    for (int i : a)
    {
        std::cout << i << " ";
    }
}