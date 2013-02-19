#include <iostream>

template <typename T>
constexpr auto add(T a, T b) -> decltype(a+b)
{
    return a + b ;
}

template <typename T>
constexpr auto subtract(T a, T b) -> decltype(a-b)
{
    return a - b ;
}

template <typename T>
constexpr auto multiply(T a, T b) -> decltype(a*b)
{
    return a * b ;
}

template <typename T>
constexpr auto divide(T a, T b) -> decltype(a/b)
{
    return (b==0) ? 0 : a/b ;
}

int main() 
{
    const int a = add(2, 3); //Example of compile-time calculation !
    int array[subtract(4, 1)]; //Yet another example !
    std::cout << "\n\nHere is the sum  " <<  a ; 
    return 0;
}



