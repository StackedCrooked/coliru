#include <vector>
#include <iostream>

int main()
{
    auto ptr1 = &std::vector<void *>::emplace_back<void *>;
    auto ptr2 = &std::vector<int *>::emplace_back<int *>;

    void *p1 = *(void **)&ptr1;
    void *p2 = *(void **)&ptr2;

    std::cout << (p1 == p2) << std::endl;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
}
