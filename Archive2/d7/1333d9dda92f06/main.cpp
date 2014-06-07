#include <typeinfo>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>
#include <tuple>

using namespace std;

struct Widget{
    int i = 0;
};

template<typename T>
T &&foo2(T &&t){
    return std::forward<T>( t );
}


template<typename T>
typename std::tuple_element<0, typename std::decay<T>::type >::type  &&foo(T &&t){
    return std::forward< typename std::tuple_element<0, typename std::decay<T>::type >::type >
            ( std::get<0>(t) );
}

Widget w;
auto list = std::make_tuple(
    Widget() /*w*/,
    Widget()
);

template<typename T>
auto foo3(T &&t) -> decltype(std::get<0>( std::forward<T>(t) ) ) {
    return std::get<0>( std::forward<T>(t) );
}

template<typename T>
auto foo4(T &&t) -> decltype(std::get<0>( std::forward<T>(t) ).i ) {
    return std::get<0>( std::forward<T>(t) ).i;
}


int main()
{
//auto &l  = foo(list );
//auto &l2 = foo2( std::get<0>(list) );     // This wokrs.
    foo3(list).i = 100;
    auto &l3  = foo3(list);
    std::cout << std::is_rvalue_reference<decltype(l3)>::value << std::endl;
    std::cout << foo3(list).i;
    
    auto &l4  = foo4(list);
    
}
