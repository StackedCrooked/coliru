#include <iostream>
#include <utility>
#include <memory>

constexpr int foo()
{
    return *std::make_unique<int>(42);
}

int main() 
{
    foo();
    return 0;
}
