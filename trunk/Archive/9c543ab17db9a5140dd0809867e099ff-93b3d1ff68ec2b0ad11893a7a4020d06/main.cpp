#include <tuple>
#include <iostream>

template <class... Args>
void f(Args&&... args)
{
    auto arguments = std::make_tuple(std::forward<Args>(args)...);
    std::cout << std::get<0>(arguments);
}

void f() {}

int main()
{
    f();
}