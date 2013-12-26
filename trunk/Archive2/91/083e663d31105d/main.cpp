#include <iostream>
#include <type_traits>


template<typename T> using Invoke   = typename T::type;
template<typename T> using InvokeIf = typename std::enable_if<T::value>::type;


template<class T>
auto function_impl(T t, InvokeIf<std::is_integral<T>>*)
{
    std::cout << "integral" << std::endl;
    return;
}


template<class T>
auto function_impl(T t, InvokeIf<std::is_floating_point<T>>*)
{
    std::cout << "floating" << std::endl;
    return;
}


template<class T>
auto function(T t)
{
    function_impl(t, 0);
    return;
}


int main()
{
    function(1);    //prints "integral"
    function(3.14); //prints "floating"
}
