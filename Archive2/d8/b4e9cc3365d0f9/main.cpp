#include <vector>
#include <iostream>
#include <iterator>

int main(int, char**)
{
    std::vector<int> test = {1, 2, 3 ,4, 5};
    for (auto it = std::rbegin(test); it != std::rend(test); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}
