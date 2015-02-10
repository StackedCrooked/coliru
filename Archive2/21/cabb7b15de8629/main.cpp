#include <string>
#include <utility>
#include <type_traits>
#include <iostream>

struct Base
{};

struct Derived : Base
{
    std::string Test(int) { return "Hello"; }
};

struct Exp
{
template <typename T = Derived, typename... TArgs>
auto Test(std::enable_if_t<std::is_base_of<Base, T>::value, T>&& obj, TArgs&&... args)
    -> decltype(obj.Test(std::forward<TArgs>(args)...))
{
    return obj.Test(std::forward<TArgs>(args)...);
}

template <typename T = Derived, typename... TArgs>
auto Test(TArgs&&... args)
    -> decltype(Test(T{}, std::forward<TArgs>(args)...))
{
    return Test(T{}, std::forward<TArgs>(args)...);
}
};
int main()
{
    std::cout << Exp().Test(123) << std::endl;
}
