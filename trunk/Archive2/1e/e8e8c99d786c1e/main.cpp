#include <iostream>
#include <vector>
#include <type_traits>

template<bool b> struct booltype {};

class A {
public:
    virtual void foo() = 0;
};

template <typename T, bool = std::is_base_of<A, T>::value, typename U = booltype<true> >
class B : public A {
public:
    void foo() override { std::cout << "A is not base of T!" << std::endl; }
};


template <typename T>
class B<T, true, booltype<true> > : public A {
public:
    void foo() override { std::cout << "A is base of T!" << std::endl; }
};

template <typename T>
class B<std::vector<T>, false, booltype<!std::is_base_of<A, T>::value> > : public A {
public:
    void foo() override { std::cout << "Vector of Ts!" << std::endl; }
};

template <typename T>
class B<std::vector<T>, false, booltype<std::is_base_of<A, T>::value> > : public A {
public:
    void foo() override { std::cout << "Vector of Ts where A is a base of T!" << std::endl; }
};

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
    B<std::vector<C> > quux;
    quux.foo();
}