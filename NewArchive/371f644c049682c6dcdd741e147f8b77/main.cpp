#include <iostream>
#include <string>


template<typename T> struct A;
template<typename T> struct B;
template<typename T> struct C;

template<typename T>
struct A
{
    B<T> operator->();
    T t;
};

template<typename T>
struct B
{
    B(T & t) : t(t) {}
    C<T> operator->();
    T t;
};

template<typename T>
struct C
{
    C(T& t) : t(t) {}
    T* operator->() { return &t; }
    T t;
};

    
B  A::operator->() { return B<T>(t); }  
C  B::operator->() { return C<T>(t); }

int main()
{
    A<std::string> a;
    a->size();
}