#include <iostream>

template<bool, class = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template<class, class>
struct is_same { static const bool value = false; };

template<class T>
struct is_same<T,T> { static const bool value = true; };

struct A {
    template<typename T>
    A(T& arg, typename enable_if<!is_same<T, A>::value>::type * = 0) { std::cout << "template\n"; }
};

int main()
{
    int i = 42;
    A a(i);  // template ctor
    A b(a);   // copy ctor
    A c = b;  // copy ctor
}