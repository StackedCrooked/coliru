#include <iostream>
#include <type_traits>


template<class T>
auto function(T t, typename std::enable_if<std::is_integral<T>::value>::type* = 0)
{
    std::cout << "integral" << std::endl;
}


template<class T>
auto function(T t, typename std::enable_if<std::is_floating_point<T>::value>::type* = 0)
{
    std::cout << "floating" << std::endl;
}


int main()
{
    function(1);    //prints "integral"
    function(3.14); //prints "floating"
}
