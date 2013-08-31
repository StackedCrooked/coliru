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

template<bool> struct IsAlphabetic {};
template<bool> struct IsNumeric    {};

using Number = Decorate<int , Numeric>;
using Letter = Decorate<char, Alphabetic>;
using Character = Decorate<char, Alphabetic, Numeric>;


template<typename T>
void print_(T t, IsAlphabetic<true>, IsNumeric<true>) {
    std::cout << "Alphanumeric: " << t << std::endl;
}

template<typename T>
void print_(T t, IsAlphabetic<true>, IsNumeric<false>) {
    std::cout << "Alphabetic: " << t << std::endl;
}

template<typename T>
void print_(T t, IsAlphabetic<false>, IsNumeric<true>) {
    std::cout << "Numeric: " << t << std::endl;
}

template<typename T>
void print(T t) {
    print_(t,
           IsAlphabetic<std::is_base_of<Alphabetic, T>::value>(),
           IsNumeric<std::is_base_of<Numeric, T>::value>());
}


int main() {    
    print(Number{});
    print(Letter{'L'});
    print(Character{'c'});
    
    Int32 i{3}, j{4}, k{5};
    std::cout << (i + j - k) << std::endl;
};
