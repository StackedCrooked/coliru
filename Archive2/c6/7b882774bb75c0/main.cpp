#include <iostream>
#include <string>
#include <type_traits>

namespace robor
{
    template <typename T>
    struct enable_if_t : std::enable_if<T::value, int> {};
    template <typename T>
    struct disable_if_t : std::enable_if<!T::value, int> {};
    
    template <typename T>
    using EnableIf = typename enable_if_t<T>::type;

    template <typename T>
    using DisableIf = typename disable_if_t<T>::type;
}


struct trivial
{
    float f;
    int i;
};

//only for trivial Ts
template <typename T, robor::EnableIf<std::is_trivial<T>> = 0>
T foo()
{
    T t;
    /* stuff */
    return t;
}

//how do I enable foo when specialized for trivial Ts?
template<>
std::string foo()
{
    std::string s;
    /* stuff */
    return s;
}

int main()
{
    trivial t = foo<trivial>();
    std::string s = foo<std::string>();
}