#include <iostream>
#include <thread>

template<typename...T>
class pack{};

template<typename...T>
struct getArgs{};
template<typename C,typename R,typename...Args>
struct getArgs<R(C::*)(Args...)>{using Type=pack<Args...>;};

template<typename T>
struct func1{
    constexpr T operator()(T x){return x+1;}
};

getArgs<decltype(&func1<int>::operator())>::Type v;

int main()
{
    
}