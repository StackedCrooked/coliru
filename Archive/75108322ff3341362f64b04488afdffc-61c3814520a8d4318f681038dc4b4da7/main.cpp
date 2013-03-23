#include <boost/operators.hpp>
#include <iostream>
#include <tuple>
#include <stdint.h>


template<typename T>
struct DefaultWrap : std::tuple<T> {
    DefaultWrap(const T & t = T{}) : std::tuple<T>(t) {}    
    friend std::ostream& operator<<(std::ostream & os, const DefaultWrap<T> & t) { return os << std::get<0>(t); }
};


template<typename T>
struct NumericWrap : DefaultWrap<T>, boost::operators<NumericWrap<T>>
{
    NumericWrap(T t = T{}) : DefaultWrap<T>(t) {}    
    operator T() const { return std::get<0>(*this); }    
    void operator +=(NumericWrap<T> v) { std::get<0>(*this) += v; }    
    void operator -=(NumericWrap<T> v) { std::get<0>(*this) -= v; }
};


template<typename T>
using Wrap = typename std::conditional<std::is_integral<T>::value, NumericWrap<T>, DefaultWrap<T>>::type;


using Int16 = Wrap<int16_t>;
using Int32 = Wrap<int32_t>;
using Int64 = Wrap<int64_t>;


template<typename T, class Head, class ...Tail>
struct Decorate : Head, Decorate<T, Tail...> {    
    Decorate(const T & t = T{}) : Head(), Decorate<T, Tail...>(t) {}
};

template<typename T, class Head>
struct Decorate<T, Head> : Head, Wrap<T> {
    Decorate(const T & t = T{}) : Wrap<T>(t) {}
};

struct Alphabetic {};
struct Numeric    {};

template<typename> struct IsAlphabetic       : std::false_type {};
template<>         struct IsAlphabetic<char> : std::true_type {};

template<typename> struct IsNumeric           : std::false_type {};
template<>         struct IsNumeric<int8_t >  : std::true_type  {};
template<>         struct IsNumeric<int16_t>  : std::true_type  {};
template<>         struct IsNumeric<int32_t>  : std::true_type  {};
template<>         struct IsNumeric<int64_t>  : std::true_type  {};
template<>         struct IsNumeric<uint8_t > : std::true_type  {};
template<>         struct IsNumeric<uint16_t> : std::true_type  {};
template<>         struct IsNumeric<uint32_t> : std::true_type  {};
template<>         struct IsNumeric<uint64_t> : std::true_type  {};


template<template<class, typename ...> class WrapType, typename Head, typename ...Tail>
struct IsNumeric<WrapType<Head, Tail...>> : IsNumeric<Head> {};


template<template<class, typename ...> class WrapType, typename Head, typename ...Tail>
struct IsAlphabetic<WrapType<Head, Tail...>> : IsAlphabetic<Head> {};


using Number    = Decorate<int , Numeric>;
using Letter    = Decorate<char, Alphabetic>;
using Character = Decorate<char, Alphabetic, Numeric>;

struct is_alphabetic_tag   {};
struct is_numeric_tag      {};
struct is_alphanumeric_tag {};


template<typename T>
void print_(T t, is_alphanumeric_tag) {
    std::cout << "Alphanumeric: " << t << std::endl;
}

template<typename T>
void print_(T t, is_alphabetic_tag) {
    std::cout << "Alphabetic: " << t << std::endl;
}

template<typename T>
void print_(T t, is_numeric_tag) {
    std::cout << "Numeric: " << t << std::endl;
}

template<typename T>
void print(T t) {
    print_(t,
           typename std::conditional<
                IsNumeric<T>::value,
                typename std::conditional<IsAlphabetic<T>::value, is_alphanumeric_tag, is_numeric_tag >::type,
                is_alphabetic_tag
            >::type());
}


int main() {    
    print(Number{42});
    print(Letter{'L'});
    print(Character{'c'});
    
    Int32 i{3}, j{4}, k{5};
    std::cout << (i + j - k) << std::endl;
};
