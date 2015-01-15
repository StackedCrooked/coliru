#include <iostream>
template <class T>
class A {};

template <class T>
class B {
public:
    B(){};
};

template <class T>
class C : public B<A<T>> {
public:
    using Base = B<A<T>>;
    using Base::Base;
};

static C<int> c;

int main()
{
}
