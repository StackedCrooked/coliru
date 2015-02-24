#include <memory>
#include <utility>
#include <iostream>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main()
{
    auto obj = make_unique<int>(2);
    
    std::cout << *obj << std::endl;
}