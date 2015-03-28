#include<type_traits>
#include<iostream>

namespace impl
{
    template<typename ... Args> struct A {};
    template<typename T> struct A<T>
    {
        A() {std::cout<<"I'm an A"<<std::endl;}
    };

    template<typename ... Args> struct B {};
    template<typename T, typename V> struct B<T, V>
    {
        B() {std::cout<<"I'm a B"<<std::endl;}
    };
}

template<typename ... Args>
using C = typename std::conditional<sizeof...(Args)==1, typename impl::A<Args ...>, typename impl::B<Args ...> >::type;

int main()
{
    C<double> a;            //prints "I'm an A"
    C<double, int> b;       //prints "I'm a B"
}