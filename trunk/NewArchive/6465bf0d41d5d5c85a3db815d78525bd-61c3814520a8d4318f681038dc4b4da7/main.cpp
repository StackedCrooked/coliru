#include <iostream>
#include <tuple>
#include <stdint.h>


template<typename T>
struct DefaultWrap : std::tuple<T> {
    DefaultWrap(const T & t = T{}) : std::tuple<T>(t) {}    
    friend std::ostream& operator<<(std::ostream & os, const DefaultWrap<T> & t) { return os << std::get<0>(t); }
};

template<typename T>
struct Wrap : DefaultWrap<T> {
    Wrap(const T & t = T{}) : DefaultWrap<T>(t) {}
};


template<typename T, class Head, class ...Tail>
struct Decorate : Head, Decorate<T, Tail...> {    
    Decorate(const T & t = T{}) : Head(), Decorate<T, Tail...>(t) {}
};

template<typename T, class Head>
struct Decorate<T, Head> : Head, DefaultWrap<T> {
    Decorate(const T & t = T{}) : DefaultWrap<T>(t) {}
};


struct Alphabetic {};
struct Numeric    {};

template<bool> struct IsAlphabetic {};
template<bool> struct IsNumeric    {};


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
    using Number    = Decorate<int , Numeric>;
    print(Number{});     
    
    using Letter    = Decorate<char, Alphabetic>;
    print(Letter{'L'});    
    
    using Character = Decorate<char, Alphabetic, Numeric>;
    print(Character{'c'});
};
