#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v1 { -1, 10, -7, 8, 9, 10 };
    std::vector<int> neg;
    std::vector<int> pos;

    std::partition_copy(v1.begin(),
                        v1.end(),
                        std::back_inserter(neg),
                        std::back_inserter(pos),
                        [](int i) { return i < 0; });

    std::cout << "neg: ";
    for (auto i: neg) std::cout << i << ", ";
    std::cout << std::endl;

    std::cout << "pos: ";
    for (auto i: pos) std::cout << i << ", ";
    std::cout << std::endl;
}
