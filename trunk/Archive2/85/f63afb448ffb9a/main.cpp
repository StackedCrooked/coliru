#include <cstddef>
#include <utility>

template <typename T>
struct array_traits {
    using type = void;
};

template <typename T>
struct array_traits<T[]> {
    using type = T&;
};

template <typename T>
struct foo {
    T t;

    foo() {}
    foo(T value) : t(std::move(value)) {}
    ~foo() {}

    T get() const { return t; }
    void set(const T& value) { t = value; }
    void set(T&& value) { t = std::move(value); }

    typename array_traits<T>::type operator [] (std::size_t i) { return t[i]; }
};

#if 0
// instantiate entire class: triggers an error trying to instantiate foo<int>::operator []
template struct foo<int>;
#else
// only instantiate well-formed members: no error
template foo<int>::foo();
template foo<int>::foo(int);
template foo<int>::~foo();
template int foo<int>::get() const;
template void foo<int>::set(const int&);
template void foo<int>::set(int&&);
#endif
