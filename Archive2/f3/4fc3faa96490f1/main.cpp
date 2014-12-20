#include <future>
#include <memory>
#include <iostream>

std::unique_ptr<int> foo()
{
    return std::make_unique<int>(42);
}

int main()
{
    auto f = std::async(foo);
    
    auto result = f.get();
    
    std::cout << *result;
}