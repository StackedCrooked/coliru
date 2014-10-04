
#include <iostream>

template<typename T> 
auto foo(T a, T b) -> decltype(a+=b);

template<typename T> 
auto foo(T a, T b) -> decltype(bar(a,b));

int main()
{
    std::cout << "its compile fine" << std::endl;
}
