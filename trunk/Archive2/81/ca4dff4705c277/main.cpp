#include <iostream>
#include <type_traits>

template<typename T, typename... Interfaces>
typename std::enable_if<sizeof...(Interfaces) == 0, bool>::type
 TryQueryInterfaces()    
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return false;
}

template<typename T, typename... Interfaces>
typename std::enable_if<sizeof...(Interfaces) != 0, bool>::type
 TryQueryInterfaces()    
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return TryQueryInterfaces<T>() || TryQueryInterfaces<Interfaces...>();
}

struct Foo1 {};
struct Foo2 {};
struct Foo3 {};

int main()
{
    TryQueryInterfaces<Foo1, Foo2, Foo3>();
}
