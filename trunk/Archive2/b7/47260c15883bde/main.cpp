#include <array>
#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>

template<typename ...Args>
void scan(std::function<void(Args...)> f, Args... a)
{
    f(a...);
}

int main()
{
    scan([](int a) {
        std::cout << a << std::endl;
    }, 4);
}

