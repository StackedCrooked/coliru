#include <iostream>
#include <typeinfo>
#include <type_traits>

using namespace std;



template<typename T1, typename T2>
struct Tsmaller : std::integral_constant<bool, sizeof(T1) < sizeof(T2)> {
};

template<template<typename, typename> class Compare = Tsmaller> struct TTMin {

//  Unspecialized version
template<typename...Ts>
struct Tmin
{ 
    using type = void;
};

template<typename T>
struct Tmin<T>
{
    using type = T;
};


template<typename T1, typename T2, typename...Ts>
struct Tmin<T1, T2, Ts...>
{
    using type = typename std::conditional<Compare<T1, T2>::value, 
        typename Tmin<T1, Ts...>::type, typename Tmin<T2, Ts...>::type
        >::type;
};

};

int main()
{
    cout << typeid(TTMin<>::Tmin<float, int, double>::type).name() << endl;
    return 0;
}
