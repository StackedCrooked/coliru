#include <boost/operators.hpp>
#include <iostream>
#include <tuple>
#include <stdint.h>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

template<typename T>
struct DefaultWrap : std::tuple<T>
{
    template<typename ...Args>
    DefaultWrap(Args && ...args) : std::tuple<T>(std::forward<Args>(args)...) {}
    
    friend std::ostream& operator<<(std::ostream & os, const DefaultWrap<T> & t)
    {
        return os << std::get<0>(t);
    }
};

template<typename T>
struct Wrap : DefaultWrap<T>
{
    template<typename ...Args>
    Wrap(Args && ...args) : DefaultWrap<T>(std::forward<Args>(args)...) {}
};

template<typename T, class Head, class ...Tail>
struct Decorate : Head, Decorate<T, Tail...>
{
    template<typename ...Args>
    Decorate(Args && ...args) : Decorate<T, Tail...>(std::forward<Args>(args)...) {}
};

template<typename T, class Head>
struct Decorate<T, Head> : Head, DefaultWrap<T>
{
    template<typename ...Args>
    Decorate(Args && ...args) : DefaultWrap<T>(std::forward<Args>(args)...) {}
};


struct Alphabetic {};
struct Numeric {};

using Letter    = Decorate<char, Alphabetic>;
using Number    = Decorate<int , Numeric>;
using Character = Decorate<char, Alphabetic, Numeric>;


template<bool> struct IsAlphabetic {};
template<bool> struct IsNumeric    {};


template<typename T>
void print_(T t, IsAlphabetic<true>, IsNumeric<true>)
{
    std::cout << "Alphanumeric: " << t << std::endl;
}

template<typename T>
void print_(T t, IsAlphabetic<true>, IsNumeric<false>)
{
    std::cout << "Alphabetic: " << t << std::endl;
}

template<typename T>
void print_(T t, IsAlphabetic<false>, IsNumeric<true>)
{
    std::cout << "Numeric: " << t << std::endl;
}

template<typename T>
void print(T t)
{
    print_(t,
           IsAlphabetic<std::is_base_of<Alphabetic, T>::value>(),
           IsNumeric<std::is_base_of<Numeric, T>::value>());    
}

int main()
{
    Letter l = 'L';    
    print(l);
    
    Number n = 4;
    print(n);
    
    Character c = 'c';
    print(c);
};
