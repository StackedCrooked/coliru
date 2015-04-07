#include <iostream>
#include <utility>

template<class T>
struct foo {
    T t;
    void Set(T&& in){ t = std::move(in); };
    void Set(T const& in){ t = in; };
    template<class U>
    void Set(U&& in){ t = std::forward<U>(in); }
};

int main() {
    foo<int> x;
    x.Set( 3.14 ); // calls #3
    x.Set( x.t ); // calls #2
    x.Set( {3} ); // calls #1
    x.Set( {} ); // also calls #1
    x.Set( 3 ); // calls #1
}