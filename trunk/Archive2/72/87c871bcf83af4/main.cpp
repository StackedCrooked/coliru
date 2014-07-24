#include <iostream>
#include <type_traits>
class A {
public:
    virtual void foo() = 0;
};

template <class T, bool = std::is_base_of<A, T>::value>
class B : public A {
public:
    void foo() override { std::cout << "A is not base of T!" << std::endl; }
};


template <class T>
class B<T, true> : public A {
public:
    void foo() override { std::cout << "A is base of T!" << std::endl; }
};

class C : A {
public:
    void foo() { }
};

class D  { };

int main() {
    B<C> bar;  // I was like "this is gonna work!! :) :D"
    bar.foo(); // But this calls B::foo() instead of B<A>::foo()... :'( *sob*
    B<D> baz;
    baz.foo();
}
    