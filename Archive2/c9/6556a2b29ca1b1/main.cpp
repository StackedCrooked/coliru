#include <iostream>
#include <cstddef>
int main()
{
    int a;
    std::cin >> a;
    std::cout << alignof(std::max_align_t) << '\n';
}