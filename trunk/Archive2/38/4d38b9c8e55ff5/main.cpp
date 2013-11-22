#include <iostream>

template<typename T>
struct type {
    template<typename>
    struct impl;

    type();
    ~type();

    void m();

private:
    typedef impl<T> Impl;
    impl<T> *pimpl;
};

template<typename T>
template<typename A>
struct type<T>::impl {
    impl();

    T t;
    A a;
};
template<typename T>
template<typename A>
type<T>::impl<A>::impl()
{}

template<typename T>
type<T>::type()
    :pimpl(new type<T>::Impl)
{}
template<typename T>
type<T>::~type()
{ delete pimpl; }
template<typename T>
void type<T>::m()
{std::cout << "ping!" << std::endl;}

int main() {
    type<int> t;
    t.m();
}