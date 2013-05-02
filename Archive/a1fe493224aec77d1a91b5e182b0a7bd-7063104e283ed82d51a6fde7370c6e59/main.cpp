#include <iostream>
#include <list>

int main()
{
    std::list<int> l1, l2;
    l2.insert(l1.begin(), 42);

    std::cout << "First" << std::endl;
    for(const auto& elem: l1)
        std::cout << elem << ' ';
    std::cout << std::endl;

    std::cout << "Second" << std::endl;
    for(const auto& elem: l2)
        std::cout << elem << ' ';
    std::cout << std::endl;
    return 0;
}
