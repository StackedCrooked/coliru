#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct Bar {};

std::function<void()> foo(const Bar & b)
{
    return [b]() { std::cout << "captured b=" << &b << std::endl; };
}

int main()
{
    std::vector<std::function<void()>> callbacks;
    {
        Bar b;
        callbacks.emplace_back(foo(b));
        std::cout << "b=" << &b << std::endl;
    }
    callbacks.front()();
}
