#include <iostream>
#include <memory>

template<typename T>
struct Holder
{
    Holder() : ptr(new T, [](T*){}) {}
    
    std::weak_ptr<T> get_weak_ptr() { return std::weak_ptr<T>{ptr}; }
    
    std::shared_ptr<T> ptr;
};

int main()
{
    Holder<std::string> name;
    std::cout << (*name.get_weak_ptr().lock().operator->() = "John");
}