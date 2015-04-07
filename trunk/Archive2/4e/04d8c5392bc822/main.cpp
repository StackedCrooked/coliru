#include <iostream>
template <class T, class V> class C{ };

template <class T, class V, class W> class D{ };

template
<
    class T,
    class V,
    class W
>
class A;

template
<
    class T1,
    class T2,
    class T3,
    class V,
    class W
>
class A<D<T1, T2, T3>, V, W>
{
public:
    void foo(){ std::cout << "foo()!!!!" << std::endl; }
};


template
<
    class T1,
    class T2,
    class V,
    class W
>
class A<C<T1, T2>, V, W>
{
public:
    void foo(){ std::cout << "foo()" << std::endl; }
};

A<D<int, int, int>, int, int> a;

A<C<int, int>, int, int> b;

int main(){ a.foo(); b.foo(); }