#include <iostream>
#include <initializer_list>

void func(std::initializer_list<int> a_args)
{
    for (auto i: a_args) std::cout << i << '\n';
}

int main()
{
    func({4, 7});
    func({4, 7, 12, 14});
}