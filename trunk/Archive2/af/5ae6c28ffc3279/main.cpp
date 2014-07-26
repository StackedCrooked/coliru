#include <iostream>

template <typename... Ts>
struct foo
{
    template <size_t N>
    void bar();
};

template <>
template <>
void foo<int, float>::bar<0>()
{ std::cout << "ok, good 0" << std::endl; }

int main()
{
    foo<int, float>{}.bar<0>();
}
