#include <iostream>
#include <type_traits>

template<typename T, typename U>
struct EnableWhenEqual : std::enable_if<std::is_same<T, U>::value>
{
};

template<typename T, typename U, typename Enable = typename EnableWhenEqual<T,U>::type >
void foo(T&&, U&&)
{
    if (std::is_same<T,U>::value)
        std::cout << "OK, overload allowed." << std::endl;
    else
        std::cout << "Bad. Should not compile!" << std::endl;
}


int main()
{
    foo(1,1);     //prints "OK, overload allowed"
   // foo(1,2.0); // error: no matching function for call
}