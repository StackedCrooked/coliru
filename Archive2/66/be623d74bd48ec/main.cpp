#include <iostream>

template <typename T, size_t N>
struct hermitian_matrix { };

struct foo
{
    template <typename T>
    using pauli = hermitian_matrix<T, 2>;
    
    template <typename T>
    constexpr static pauli<T> sigma1 = { { 0, 1 }, { 1, 0 } };
};


struct foo5
{
    template <typename T>
    static T pi = T{3.14};
};

template <typename T>
struct foo2
{
    template <typename U = T>
    U pi = U{3.14};
};

template <typename T>
struct foo3
{
    template <T>
    static T pi = 42;
};

struct foo6
{
    template <typename T>
    static T bar;
};

template <typename T>
T foo6::bar = T{3.14};