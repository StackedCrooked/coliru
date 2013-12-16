#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <typeinfo>

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

namespace impl {
  template <typename T>
  T* add_x(T* t, decltype (x<T> (nullptr), int { })) noexcept
  {
    return t;
  }

  template <typename T>
  Y<T>* add_x(T* t, ...) noexcept
  {
    auto ret = new Y<T>;
    ret->base = t;
    return ret;
  }
}

template<typename T>
auto add_x (T * t) -> decltype (impl::add_x (t, 0))
{
  return impl::add_x (t, 0);
}

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
    auto b = new Y<Z<X>>;
    x(b) = 1;
    
    auto a2 = add_x(a);
    auto b2 = add_x(b);
    x(a2) = 2;
    x(b2) = 3;
    
    std::cout << x(b) << " " << x(a2) << " " << x(b2) << std::endl;
    // should print 3 2 3
}   
  return 0;
}