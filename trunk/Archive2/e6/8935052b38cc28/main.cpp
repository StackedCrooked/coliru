#include <iostream>
#include <utility>

template<class...>struct voider{using type=void;};
template<class...Ts>using void_t=typename voider<Ts...>::type;

template<class T>
void f(std::conditional_t< std::is_same<T,double>::value, T, void >)
{
    std::cout << "hello world!\n";
}

int main() {
    f<int>(); // error, int does not have a nested type foo
}