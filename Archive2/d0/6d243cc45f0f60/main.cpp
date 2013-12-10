#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>

struct X {
};

template <typename _Base>
struct Y {
    typedef _Base Base;
    Base* base;
    int x;
};

template <typename _Base>
struct Z {
    typedef _Base Base;
    Base* base;
};

template <typename T>
struct has_x {
    static const bool value = false;
};
template <typename T>
struct has_x<Y<T>> {
    static const bool value = true;
};
template <typename T>
int& x(T* t) noexcept;
template <bool has>
struct XImpl {
    template <typename T>
    static int& apply(T* t) noexcept {
        return x<typename T::Base>(t->base);
    }
};
template <>
struct XImpl<true> {
    template <typename T>
    static int& apply(T* t) noexcept {
        return t->x;
    }
};
template <typename T>
int& x(T* t) noexcept {
    return XImpl<has_x<T>::value>::apply(t);
}

/// The problem part \v
/*
template <typename T, IF x(some T) would succeed>
T* add_x(T* t) noexcept
{
    return t;
}
template <typename T, IF x(some T) would fail>
Y<T>* add_x(T* t) noexcept
{
    auto ret = new Y<T>;
    ret->base = t;
    return ret;
}*/
///

int main() {
{
    auto a = new Y<X>; a->x = 10;
    auto b = new Z<Z<Y<X>>>;
    b->base = new Z<Y<X>>;
    b->base->base = new Y<X>;
    b->base->base->x = 20;
    
    std::cout << x(a) << std::endl;
    std::cout << x(b) << std::endl;
}
    //..
{   
    auto a = new Z<X>;
    auto b = new Z<Z<Y<Z<X>>>>;
    
    std::cout << typeid(decltype(add_x(a))).name() << std::endl; // should be Y<Z<X>>
    std::cout << typeid(decltype(add_x(b))).name() << std::endl; // should remain Z<Z<Y<Z<X>>>>
}   
	return 0;
}