#include <stdio.h>

#include <type_traits>

template< class T > struct is_pointer_helper     : std::false_type {};
//template< class T > struct is_pointer_helper2    {};
template< class T > struct is_pointer_helper<T*> : std::true_type {};
template< class T > struct is_pointer : is_pointer_helper<typename std::remove_cv<T>::type> {};

template<class X> struct my_tester: std::false_type{};

class A{};

int main() 
{
    struct my_tester<A> aaa;
    printf("test%d", aaa.value);

}