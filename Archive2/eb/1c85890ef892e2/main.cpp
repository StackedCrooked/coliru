#include <type_traits>

template<typename T>
class Base
{
public:
    using Storage = typename std::aligned_storage<sizeof(T), alignof(T)>::type; 

    Base(Storage*)
    {}
};

template<typename T>
class Derived : public Base<T>
{
public:
    using Storage = typename Base<T>::Storage;

    Derived(Storage* storage)
        : Base<T>{storage}
    {}
};

int main()
{
    Derived<int>::Storage storage;  
    Derived<int> derived {&storage};
}