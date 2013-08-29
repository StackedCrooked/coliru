#include <iostream>
#include <memory>

std::unique_ptr<int> a()
{
    std::unique_ptr<int> ptr(new int());
    return ptr;
}

std::unique_ptr<int> b()
{
    static std::unique_ptr<int> ptr(new int());
    return std::move(ptr);
}

int main()
{
    std::cout << a().get() << std::endl;
    std::cout << a().get() << std::endl;
    
    std::cout << std::endl;
    
    std::cout << b().get() << std::endl;
    std::cout << b().get() << std::endl;
}