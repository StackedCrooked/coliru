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

template<typename T>
auto foo3(T &&t) -> decltype(std::get<0>(t)) {
    return std::get<0>(t);
}

int main()
{
//auto &l  = foo(list );
//auto &l2 = foo2( std::get<0>(list) );     // This wokrs.
    auto &&l3  = foo3(std::forward_as_tuple(
                    Widget(),
                    Widget()
                ) );
    std::cout << std::is_rvalue_reference<decltype(l3)>::value;

}
