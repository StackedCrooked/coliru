#include <memory>
#include <functional>
#include <iostream>

template<typename T>
using erased_deleter = std::function<void(T*)>;

template<typename T>
using erased_unique_ptr = std::unique_ptr<T, erased_deleter<T>>;

template<typename T, typename... Args>
erased_unique_ptr<T> make_erased_unique(erased_deleter<T> deleter, Args&&... args)
{
    return erased_unique_ptr<T>{new T{std::forward<Args>(args)...}, std::move(deleter)};
}

int main()
{
    auto d = [] (int* p) { std::cout << *p << std::endl; delete p; };
    
    {
        auto p = make_erased_unique<int>(d, 42);
    }
    
    std::cout << "deleted" << std::endl;
}