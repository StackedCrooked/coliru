#include <iostream>
#include <memory>

int main()
{
    auto uptr = std::make_unique<const int>(42);
}