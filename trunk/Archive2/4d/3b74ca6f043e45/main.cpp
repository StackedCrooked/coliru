#include <typeinfo>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>
#include <tuple>

using namespace std;

class Widget{};

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
    /*Widget()*/w,
    Widget()
);


int main()
{
    
auto &l  = foo(list );
//auto &l2 = foo2( std::get<0>(list) );     // This wokrs.

}
