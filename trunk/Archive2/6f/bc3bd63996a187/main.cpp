#include <utility>

#define _fwd(v) std::forward<decltype(v)>(v)

#define $(id) \
    [](auto&&... a) -> decltype(auto) \
    { return id(_fwd(a)...); }
    
#define $_(id) \
    [](auto&& a, auto&&... b) -> decltype(auto) \
    { return _fwd(a).id(_fwd(b)...); }

#define $left(op) \
    [](auto&& a) -> decltype(auto) \
    { return op _fwd(a); }
    
#define $right(op) \
    [](auto&& a) -> decltype(auto) \
    { return _fwd(a) op; }
    
#define $2(op) \
    [](auto&& a, auto&& b) -> decltype(auto) \
    { return _fwd(a) op _fwd(b); }

#include <iostream>

template<class T, class U>
void f(T&& t, U&& u){ t(u); }

struct X{
    template<class T>
    void f(T&& v){ std::cout << v << "\n"; }
};

int main()
{
    f($left(std::cout <<), "0\n");
    $2(<<)(std::cout, "1\n");
    $_(f)(X{}, $right(+1)(1));
    $right(<< "\n")($left(std::cout <<)("hi"));
}