#include <memory>
#include <array>

std::array<std::unique_ptr<int>, 2> f()
{
    std::array<std::unique_ptr<int>, 2> a = { { std::unique_ptr<int>(new int(1)), std::unique_ptr<int>(new int(2)) } };
    return a;
}

#include <iostream>

int main()
{
    for (auto const & p : f())
        std::cout << *p << "\n";
}
