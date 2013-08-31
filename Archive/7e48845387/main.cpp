#include <iostream>

template<class U, class V> struct S;

template<class U, class V>     using A = S<U,V>;
template<class U, class V=int> using A = S<U,V>;

template<class U, class V>     struct B;
template<class U, class V=int> struct B {};

int main()
{
    //A<int> a;    // doesn't compile
    B<int> b;      // compiles fine
}
