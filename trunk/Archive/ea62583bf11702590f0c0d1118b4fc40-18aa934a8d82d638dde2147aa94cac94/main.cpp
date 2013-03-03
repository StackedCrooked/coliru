#include <iostream>
#include <type_traits>

template<typename T, bool IsFunction = std::is_function<T>::value>
struct is_callable;

template<typename T>
struct is_callable<T, true>
{
    static const bool value = true;
};

template<typename T>
struct is_callable<T, false>
{
    // Something that works only if T is a class
};
void a() {}

int main()
{
    std::cout << std::is_function<decltype(a)>::value << std::endl; // prints true
    std::cout << is_callable<decltype(a)>::value << std::endl;

    return 0;
}