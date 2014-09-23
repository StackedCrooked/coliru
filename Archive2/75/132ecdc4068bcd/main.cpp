#include <iostream>
#include <utility>
#include <memory>

template<class T>
constexpr int foo()
{
    return *std::make_unique<int>(42);
}

int main() 
{
    foo<int>();
    return 0;
}
