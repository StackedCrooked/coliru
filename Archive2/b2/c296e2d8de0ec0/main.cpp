#include <type_traits>
#include <iostream>

template<typename T, typename U>
struct EnableWhenEqual
{
    typedef typename std::enable_if<std::is_same<T, U>::value>::type type;
};

template<typename T, typename U, typename Enable = typename EnableWhenEqual<T,U>::type >
void foo(T&& t, U&& u)
{
    if (std::is_same<T,U>::value)
        std::cout << "OK, overload allowed." << std::endl;
    else
        std::cout << "Bad. Should not compile!" << std::endl;
}

int main() 
{
    foo(1,1);
    foo(1,2.0);
}
