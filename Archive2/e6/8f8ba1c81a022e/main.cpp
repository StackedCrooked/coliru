#include <iostream>
#include <vector>
#include <type_traits>
class A {
public:
    virtual void foo() = 0;
};

template <class T, bool = std::is_base_of<A, T>::value> // These need a third param perhaps?
class B : public A {
public:
    void foo() override { std::cout << "A is not base of T!" << std::endl; }
};


template <class T>
class B<T, true> : public A {
public:
    void foo() override { std::cout << "A is base of T!" << std::endl; }
};

template <class T>
class B<std::vector<T>, false> : public A { // add std::is_base_of<A, T>::value as a third param somehow
public:
    void foo() override { std::cout << "Vector of Ts!" << std::endl; }
};

/*
template <class T>
class B<std::vector<T>, false, true> : public A {
public:
    void foo() override { std::cout << "Vector of Ts where A is a base of T!" << std::endl; }
};
*/

class C : A {
public:
    void foo() { }
};

class D  { };

int main() {
    B<C> bar;
    bar.foo();
    B<D> baz;
    baz.foo();
    B<std::vector<D> > qux;
    qux.foo();
//  B<std::vector<C> > quux; <--- I want this guy to have a specialization because C is a subclass of A
}